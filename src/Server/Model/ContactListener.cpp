#include <iostream>
#include "Car/Car.h"
#include "ContactListener.h"
#include "FixtureUserData.h"
#include "Modifier.h"
#include "Track.h"

ContactListener::ContactListener(b2World *world) : _world(world) {}

void ContactListener::BeginContact(b2Contact *contact){
    handleContact(contact, true);
}

void ContactListener::EndContact(b2Contact *contact){
    handleContact(contact, false);
}

void ContactListener::carVsGroundArea(b2Fixture* carFixture, b2Fixture* groundAreaFixture, bool began){
    Car* car = (Car*) carFixture->GetBody()->GetUserData();
    auto* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
    if (began)
        car->addGroundArea(gaFud);
    else
        car->removeGroundArea(gaFud);
}

void ContactListener::handleContact(b2Contact* contact, bool began){
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    auto* fudA = (FixtureUserData*) a->GetUserData();
    auto* fudB = (FixtureUserData*) b->GetUserData();

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
        }

    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_HEALTH_POWERUP){
        Car* car = (Car*) a->GetBody()->GetUserData();
        HealthPowerup* hpu = (HealthPowerup*) b->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            hpu->markToDelete();
            car->handleHealthPowerup(hpu->getId());
        }

    } else if (fudA->getType() == FUD_HEALTH_POWERUP && fudB->getType() == FUD_CAR){
        Car* car = (Car*) b->GetBody()->GetUserData();
        HealthPowerup* hpu = (HealthPowerup*) a->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if(began){
            hpu->markToDelete();
            car->handleHealthPowerup(hpu->getId());
        }

    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_BOOST_POWERUP){
        Car* car = (Car*) a->GetBody()->GetUserData();
        BoostPowerup* bpu = (BoostPowerup*) b->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            bpu->markToDelete();
            car->handleBoostPowerup((BoostPowerupFUD*) fudB, bpu->getId());
        }

    } else if (fudA->getType() == FUD_BOOST_POWERUP && fudB->getType() == FUD_CAR){
        Car* car = (Car*) b->GetBody()->GetUserData();
        BoostPowerup* bpu = (BoostPowerup*) a->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            bpu->markToDelete();
            car->handleBoostPowerup((BoostPowerupFUD*) fudA, bpu->getId());
        }

    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_MUD){
        Car* car = (Car*) a->GetBody()->GetUserData();
        Mud* mud = (Mud*) b->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            mud->markToDelete();
            car->handleMud((MudFUD*) fudB, mud->getId());
        }

    } else if (fudA->getType() == FUD_MUD && fudB->getType() == FUD_CAR){
        Car* car = (Car*) b->GetBody()->GetUserData();
        Mud* mud = (Mud*) a->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            mud->markToDelete();
            car->handleMud((MudFUD*) fudA, mud->getId());
        }

    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_OIL){
        Car* car = (Car*) a->GetBody()->GetUserData();
        Oil* oil = (Oil*) b->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            oil->markToDelete();
            car->handleOil((OilFUD*) fudB, oil->getId());
        }

    } else if (fudA->getType() == FUD_OIL && fudB->getType() == FUD_CAR){
        Car* car = (Car*) b->GetBody()->GetUserData();
        Oil* oil = (Oil*) a->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            oil->markToDelete();
            car->handleOil((OilFUD*) fudA, oil->getId());
        }
    } else if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_ROCK){
        Car* car = (Car*) a->GetBody()->GetUserData();
        Rock* rock = (Rock*) b->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            rock->markToDelete();
            car->handleRock((RockFUD*) fudB, rock->getId());
        }

    } else if (fudA->getType() == FUD_ROCK && fudB->getType() == FUD_CAR){
        Car* car = (Car*) b->GetBody()->GetUserData();
        Rock* rock = (Rock*) a->GetBody()->GetUserData();

        contact->SetEnabled(false);

        if (began){
            rock->markToDelete();
            car->handleRock((RockFUD*) fudA, rock->getId());
        }
    }

    if (fudA->getType() == FUD_CAR && fudB->getType() == FUD_GROUND_AREA){
        if (!((GroundAreaFUD*) fudB)->isGrass()){
            Car* car = (Car*) a->GetBody()->GetUserData();
            auto* track = (Track*) b->GetBody()->GetUserData();
            car->setTrack(track);
        }
        contact->ResetFriction();
        carVsGroundArea(a, b, began);
    } else if (fudA->getType() == FUD_GROUND_AREA && fudB->getType() == FUD_CAR){
        if (!((GroundAreaFUD*) fudA)->isGrass()){
            Car* car = (Car*) b->GetBody()->GetUserData();
            auto* track = (Track*) a->GetBody()->GetUserData();
            car->setTrack(track);
        }
        contact->ResetFriction();
        carVsGroundArea(b, a, began);
    }

}

