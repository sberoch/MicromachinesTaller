#include <iostream>
#include "Car/Car.h"
#include "ContactListener.h"

ContactListener::ContactListener(b2World *world) : _world(world) {}

void ContactListener::BeginContact(b2Contact *contact){
    std::cout << "\n\nBegin contact!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    // Get the first and second fixture in this contact
    b2Fixture* GetFixtureA();
    b2Fixture* GetFixtureB();

    //check if fixture A was a car
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->startContact(contact->GetFixtureB()->GetBody());

    //check if fixture B was a car
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->startContact(contact->GetFixtureA()->GetBody());
}

void ContactListener::EndContact(b2Contact *contact){
    std::cout << "\n\nEnd contact!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111\n";
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->endContact(contact->GetFixtureB()->GetBody());

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->endContact(contact->GetFixtureA()->GetBody());
}
