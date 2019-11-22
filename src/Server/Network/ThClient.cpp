//
// Created by alvaro on 31/10/19.
//

#include <sstream>
#include <iostream>
#include <utility>
#include "ThClient.h"
#include "../../Common/SocketError.h"
#include "../../Common/Event/EventCreator.h"


ClientThread::ClientThread(Protocol protocol, RoomController& controller, int clientId,
        std::atomic_bool& acceptSocketRunning):
        keepTalking(true),
        protocol(std::move(protocol)),
        clientId(clientId),
        player(nullptr, idFromRoom),
        receivingNonBlockingQueue(nullptr),
        sendingBlockingQueue(true),
        sender(std::ref(this->protocol), sendingBlockingQueue,
                   acceptSocketRunning, keepTalking),
        receiver(std::ref(this->protocol), this->receivingNonBlockingQueue,
                     acceptSocketRunning, keepTalking){}


void ClientThread::run() {
    std::cout << "Client started" << std::endl;
    try {
        try {
            this->sender.start();
            this->receiver.start();
        } catch (SocketError &e) {
            keepTalking = false;
        }
    } catch(const std::exception &e) {
        printf("ERROR from thClient: %s \n", e.what());
    } catch(...) {
        printf("Unknown error from thclient");
    }
}



//Si el cliente ya produjo el stop o termino de hablar, devuelve true.
bool ClientThread::isDead(){
    return !keepTalking;
}

void ClientThread::sendEvent(const std::shared_ptr<Event>& event) {
    event->send(this->protocol);
}

void ClientThread::handleInput(const InputEnum &input) {
    this->player.handleInput(input);
}

void ClientThread::assignCar(const std::shared_ptr<Car>& car){
    this->player.assignCarAndId(car);
}

void ClientThread::createModifier(const size_t& type, const size_t& id, const float& x,
        const float& y, const float& angle){
    player.createModifier(type, id, x, y, angle);
}

void ClientThread::modifySnapshotFromClient(const std::shared_ptr<SnapshotEvent>& snapshot){
    player.modifySnapshot(snapshot);
}

void ClientThread::sendSnapshot(const std::shared_ptr<SnapshotEvent>& snapshot) {
    std::shared_ptr<SnapshotEvent> newSnap(new SnapshotEvent(*snapshot.get()));
    std::shared_ptr<Event> event(newSnap);
    this->sendingBlockingQueue.push(event);
    //std::cout << "Sent\n";
}


void ClientThread::assignRoomQueue(SafeQueue<std::shared_ptr<Event>>* receiveingQueue) {
    this->receivingNonBlockingQueue = receiveingQueue;
    receiver.setQueue(receiveingQueue);
}

void ClientThread::sendStart(json j) {
    std::shared_ptr<Event> event(this->player.sendStart(std::move(j)));
    this->sendingBlockingQueue.push(event);
}

void ClientThread::sendLobbySnapshot(std::shared_ptr<LobbySnapshot>& snapshot){
    std::cout << "Enviando desde cliente: " << clientId << std::endl;
    std::shared_ptr<LobbySnapshot> newSnap(new LobbySnapshot(*snapshot.get()));
    newSnap->setPlayerId(this->clientId);
    std::shared_ptr<Event> event(newSnap);
    this->sendingBlockingQueue.push(event);
}


void ClientThread::assignIdFromRoom(int idFromRoom){
    this->idFromRoom = idFromRoom;
}

bool ClientThread::update(){
    int newNumberOfLaps = player.update();
    bool lapCompleted = numberOfLaps != newNumberOfLaps;
    if (lapCompleted)
        numberOfLaps = newNumberOfLaps;

    return lapCompleted;
}


int ClientThread::getIdFromRoom() {
    return this->idFromRoom;
}

int ClientThread::getClientId(){
    return this->clientId;
}

bool ClientThread::finishedPlaying() {
    return this->player.finishedPlaying();
}

void ClientThread::sendEndEvent(const std::shared_ptr <EndSnapshot> &endSnapshot) {
    std::shared_ptr<EndSnapshot> endSnapshotCopy(endSnapshot);
    this->sendingBlockingQueue.push(endSnapshotCopy);
}

void ClientThread::start() {
    this->run();
}

//Detiene la ejecucion del cliente y pone la variable booleana en falso
//para que el recolector de clientes muertos pueda reconocerlo como tal.
//PRIVADA.
void ClientThread::stop(){
    protocol.forceShutDown();
    sendingBlockingQueue.push(nullptr);
    keepTalking = false;

    sender.join();
    receiver.join();
}

ClientThread::~ClientThread() {
    std::cout << "Destruyendo client thread con clientId: " << clientId << std::endl;
    stop();
}

int ClientThread::getNumberOfLaps() {
    return this->numberOfLaps;
}




