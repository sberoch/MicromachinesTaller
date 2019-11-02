#include "Car/Car.h"
#include "ContactListener.h"

ContactListener::ContactListener(b2World *world){}

void ContactListener::BeginContact(b2Contact *contact){
    // Get the first and second fixture in this contact
    b2Fixture* GetFixtureA();
    b2Fixture* GetFixtureB();

    //check if fixture A was a car
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->startContact();

    //check if fixture B was a car
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->startContact();
}

void ContactListener::EndContact(b2Contact *contact){
    //check if fixture A was a ball
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->endContact();

    //check if fixture B was a ball
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Car*>( bodyUserData )->endContact();
}
