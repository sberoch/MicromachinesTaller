#include <iostream>
#include "Car/Car.h"
#include "ContactListener.h"
#include "FixtureUserData.h"

ContactListener::ContactListener(b2World *world) : _world(world) {}

void ContactListener::BeginContact(b2Contact *contact){
    std::cout << "\n\nBegin contact!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    handleContact(contact, true);
}

void ContactListener::EndContact(b2Contact *contact){
    std::cout << "\n\nEnd contact!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111\n";
    handleContact(contact, false);
}

void ContactListener::carVsGroundArea(b2Fixture* carFixture, b2Fixture* groundAreaFixture, bool began){
    Car* car = (Car*) carFixture->GetBody()->GetUserData();
    if (!car)
        std::cout << "NOT CAR\n";
    GroundAreaFUD* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
    if (began)
        car->addGroundArea(gaFud);
    else
        car->removeGroundArea(gaFud);
}

void ContactListener::handleContact(b2Contact* contact, bool began){
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    FixtureUserData* fudA = (FixtureUserData*) a->GetUserData();
    FixtureUserData* fudB = (FixtureUserData*) b->GetUserData();

    if (!fudA || !fudB){
        return;
    }

    if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_GROUND_AREA){
        std::cout << "Is ground area with " << ((GroundAreaFUD*) fudB)->frictionModifier << '\n';
        carVsGroundArea(a, b, began);
    } else if (fudA->getType() == FUD_GROUND_AREA && fudB->getType() == FUD_CAR){
        std::cout << "Is ground area with " << ((GroundAreaFUD*) fudA)->frictionModifier << '\n';
        carVsGroundArea(b, a, began);
    }

}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    FixtureUserData* fudA = (FixtureUserData*) a->GetUserData();
    FixtureUserData* fudB = (FixtureUserData*) b->GetUserData();

    if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_CAR){
        std::cout << "Cars crashing\n";
        Car* cara = (Car*) a->GetBody()->GetUserData();
        Car* carb = (Car*) b->GetBody()->GetUserData();
        cara->crash();
        carb->crash();
    }
}