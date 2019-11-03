#include <iostream>
#include "Car/Car.h"
#include "ContactListener.h"
#include "FixtureUserData.h"
#include "Modifier.h"

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

    if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_CAR){
        std::cout << "Cars crashing\n";
        Car* cara = (Car*) a->GetBody()->GetUserData();
        Car* carb = (Car*) b->GetBody()->GetUserData();

        //...world manifold is helpful for getting locations
        b2WorldManifold worldManifold;
        contact->GetWorldManifold( &worldManifold );

        b2Vec2 vel1 = a->GetBody()->GetLinearVelocityFromWorldPoint( worldManifold.points[0] );
        b2Vec2 vel2 = b->GetBody()->GetLinearVelocityFromWorldPoint( worldManifold.points[0] );
        b2Vec2 impactVelocity = vel1 - vel2;

        if (began) {
            cara->crash(impactVelocity);
            carb->crash(impactVelocity);
            //contact->SetEnabled(false);
        } else {
            std::cout << "End contact cars\n";
        }

    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_HEALTH_POWERUP){
        std::cout << "Health powerup\n";
        Car* car = (Car*) a->GetBody()->GetUserData();

        if (began)
            car->handleHealthPowerup();
    } else if (fudA->getType() == FUD_HEALTH_POWERUP && fudB->getType() == FUD_CAR){
        std::cout << "Health powerup\n";
        Car* car = (Car*) b->GetBody()->GetUserData();

        if(began)
            car->handleHealthPowerup();
    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_BOOST_POWERUP){
        std::cout << "Boost powerup\n";
        Car* car = (Car*) a->GetBody()->GetUserData();

        if (began)
            car->handleBoostPowerup();
    } else if (fudA->getType() == FUD_BOOST_POWERUP && fudB->getType() == FUD_CAR){
        std::cout << "Boost powerup\n";
        Car* car = (Car*) b->GetBody()->GetUserData();

        if (began)
            car->handleBoostPowerup();
    }

    if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_GROUND_AREA){
        std::cout << "Is ground area with " << ((GroundAreaFUD*) fudB)->frictionModifier << '\n';
        carVsGroundArea(a, b, began);
        /*if (began){
            Car* car = (Car*) a->GetBody()->GetUserData();
            car->startContact(b->GetBody());
        }*/
    } else if (fudA->getType() == FUD_GROUND_AREA && fudB->getType() == FUD_CAR){
        std::cout << "Is ground area with " << ((GroundAreaFUD*) fudA)->frictionModifier << '\n';
        carVsGroundArea(b, a, began);
        /*if (began) {
            Car* car = (Car*) b->GetBody()->GetUserData();
            car->startContact(a->GetBody());
        }*/
    }

}

