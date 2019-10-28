#ifndef MICROMACHINES_TESTCAR_H
#define MICROMACHINES_TESTCAR_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#include <cppunit/extensions/HelperMacros.h>

#include "src/Server/Model/Car/Car.h"

class CarTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( CarTest );
        CPPUNIT_TEST( testCreateCarInTheExitLine );
        //CPPUNIT_TEST( testCreateMultipleCarsInTheExitLineOneNextToEachOther );
        CPPUNIT_TEST( testPressUpKey );
        CPPUNIT_TEST( testPressDownKey );
        CPPUNIT_TEST( testPressNoKey );
        CPPUNIT_TEST( testPressUpThenNoKey );
        CPPUNIT_TEST( testPressUpThenDownKey );

        CPPUNIT_TEST(testCarDoesntTurnIfItsNotMoving);
        CPPUNIT_TEST(testPressNoneThenRight);
        CPPUNIT_TEST(testPressNoneThenLeft);

        CPPUNIT_TEST( testTurnRightWithHighManeuverabilityAndHighGrab );
        CPPUNIT_TEST( testTurnRightWithHighManeuverabilityAndLowGrab );
        CPPUNIT_TEST( testTurnRightWithLowManeuverabilityAndHighGrab );
        CPPUNIT_TEST( testTurnRightWithLowManeuverabilityAndLowGrab );
        CPPUNIT_TEST( testTurnLeftWithHighManeuverabilityAndHighGrab );
        CPPUNIT_TEST( testTurnLeftWithHighManeuverabilityAndLowGrab );
        CPPUNIT_TEST( testTurnLeftWithLowManeuverabilityAndHighGrab );
        CPPUNIT_TEST( testTurnLeftWithLowManeuverabilityAndLowGrab );
        CPPUNIT_TEST( testExplodesWhenHealthIn0 );
    CPPUNIT_TEST_SUITE_END();

private:
    b2World* world;
    Car *car1, *car2, *car3;
    float _car_x_init = 15;
    float _car_y_init = 7;
    b2Body* groundBody;
    b2FrictionJoint* joint;

public:
    void setUp(){
        b2Vec2 gravity(0, 0);
        world = new b2World(gravity);

        //Floor
        b2BodyDef bodyDef;
        bodyDef.position.Set(15, 7);
        groundBody = world->CreateBody( &bodyDef );

        b2PolygonShape polygonShape;
        b2FixtureDef fixtureDef;
        fixtureDef.friction = 0.5f;
        fixtureDef.shape = &polygonShape;
        fixtureDef.isSensor = true;

        polygonShape.SetAsBox(40, 40);
        b2Fixture* groundAreaFixture = groundBody->CreateFixture(&fixtureDef);
        float frictionModifier = 0.5;
        groundAreaFixture->SetUserData(&frictionModifier);

        b2BodyDef _carBodyDef;
        _carBodyDef.type = b2_dynamicBody;
        _carBodyDef.position.Set(15, 7);
        _carBodyDef.angle = 180 * DEGTORAD;

        b2Body* carBody = world->CreateBody(&_carBodyDef);

        car1 = new Car(carBody);

        b2FrictionJointDef fjdef;
        fjdef.collideConnected = true;
        fjdef.bodyA = car1->body();
        fjdef.bodyB = groundBody;
        fjdef.maxForce = 5;

        joint = (b2FrictionJoint*) world->CreateJoint(&fjdef);
    }

    void tearDown(){
        world->DestroyJoint(joint);
        delete world;
        //delete car1;
    }

    void testCreateCarInTheExitLine(){
        std::cout << "TESTS CAR\n";

        std::cout << "TEST create car in the exit line: \n";

        CPPUNIT_ASSERT(car1->x() == _car_x_init);
        CPPUNIT_ASSERT(car1->y() == _car_y_init);
        //CPPUNIT_ASSERT(car1->speed() == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().x == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().y == 0);

        std::cout << "OK\n";
    }

    void testCreateMultipleCarsInTheExitLineOneNextToEachOther(){
        std::cout << "TEST create multiple cars in the exit line: \n";

        CPPUNIT_ASSERT(car1->x() == _car_x_init);
        CPPUNIT_ASSERT(car1->y() == _car_y_init);

        //TODO: ver distancias entre autos
        CPPUNIT_ASSERT(car2->x() == _car_x_init + 0.1);
        CPPUNIT_ASSERT(car2->y() == _car_y_init);

        CPPUNIT_ASSERT(car3->x() == _car_x_init + 0.2);
        CPPUNIT_ASSERT(car3->y() == _car_y_init);

        std::cout << "OK\n";
    }

    void testPressUpKey(){
        std::cout << "TEST press up key: \n";

        car1->handleInput(PRESS_UP, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        //CPPUNIT_ASSERT(car1->speed() > 0);
        CPPUNIT_ASSERT(car1->linearVelocity().x == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().y > 0);

        std::cout << "OK\n";
    }

    void testPressDownKey(){
        std::cout << "TEST press down key: \n";

        car1->handleInput(PRESS_DOWN, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        //CPPUNIT_ASSERT(car1->speed() < 0);
        CPPUNIT_ASSERT(car1->linearVelocity().x == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().y < 0);

        std::cout << "OK\n";
    }

    void testPressNoKey(){
        std::cout << "TEST press no key: \n";

        car1->handleInput(PRESS_NONE, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        //CPPUNIT_ASSERT(car1->speed() == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().x == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().y == 0);

        std::cout << "OK\n";
    }

    void testPressUpThenNoKey(){
        std::cout << "TEST press up and then no key: \n";

        car1->handleInput(PRESS_UP, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();

        car1->handleInput(PRESS_NONE, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        b2Vec2 intermidiate_speed = car1->linearVelocity();
        //CPPUNIT_ASSERT(car1->speed() > 0);
        CPPUNIT_ASSERT(car1->linearVelocity().x == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().y > 0);

        std::cout << "OK\n";
        std::cout << "Loses velocity in time\n";
        car1->handleInput(PRESS_NONE, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        //CPPUNIT_ASSERT(car1->speed() < intermidiate_speed);
        CPPUNIT_ASSERT(car1->linearVelocity().x == 0);
        CPPUNIT_ASSERT(car1->linearVelocity().y < intermidiate_speed.y);

        std::cout << "OK\n";
        std::cout << "Eventually reaches zero speed\n";
        car1->handleInput(PRESS_NONE, PRESS_NONE);
		car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        //Para llegar a cero hay que hacer mas steps

        std::cout << "OK\n";
    }

    void testPressUpThenDownKey(){
        std::cout << "TEST press up and then down key: \n";

        car1->handleInput(PRESS_UP, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();

        car1->handleInput(PRESS_DOWN, PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        CPPUNIT_ASSERT(car1->linearVelocity().y < 0);

        std::cout << "OK\n";
    }

    void testCarDoesntTurnIfItsNotMoving(){
        std::cout << "TEST car doesn't turn if it's not moving \n";

        car1->handleInput(PRESS_NONE, PRESS_RIGHT);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();

        CPPUNIT_ASSERT(car1->speed() == 0);
        CPPUNIT_ASSERT(car1->angle() == 180 * DEGTORAD);

        std::cout << "OK\n";
    }

    void testPressNoneThenRight(){
        std::cout << "TEST press none then right when car is moving turns right: \n";

        car1->handleInput(PRESS_UP, PRESS_RIGHT);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        float angle = car1->angle() * RADTODEG;
        std::cout << angle << std::endl;
        CPPUNIT_ASSERT(car1->angle() < 180 * DEGTORAD);

        std::cout << "OK\n";
    }

    void testPressNoneThenLeft(){
        std::cout << "TEST press none then left when car is moving turns left: \n";

        car1->handleInput(PRESS_UP, PRESS_LEFT);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        float angle = car1->angle() * RADTODEG;
        std::cout << angle << std::endl;
        CPPUNIT_ASSERT(car1->angle() > 180 * DEGTORAD);

        std::cout << "OK\n";
    }

    void testTurnRightWithLowManeuverabilityAndLowGrab(){
        std::cout << "TEST turn right with low maneuvrability and low grab: \n";


        std::cout << "OK\n";
    }

    void testTurnRightWithLowManeuverabilityAndHighGrab(){
        std::cout << "TEST turn right with low maneuvrability and high grab: \n";

        std::cout << "OK\n";
    }

    void testTurnRightWithHighManeuverabilityAndLowGrab(){
        std::cout << "TEST turn right: \n";
        std::cout << "TEST turn right with high maneuvrability and low grab: \n";

        std::cout << "OK\n";
    }

    void testTurnRightWithHighManeuverabilityAndHighGrab(){
        std::cout << "TEST turn right with high maneuvrability and high grab: \n";

        std::cout << "OK\n";
    }

    void testTurnLeftWithLowManeuverabilityAndLowGrab(){
        std::cout << "TEST turn left with low maneuvrability and low grab: \n";

        std::cout << "OK\n";
    }

    void testTurnLeftWithLowManeuverabilityAndHighGrab(){
        std::cout << "TEST turn left with low maneuvrability and high grab: \n";

        std::cout << "OK\n";
    }

    void testTurnLeftWithHighManeuverabilityAndLowGrab(){
        std::cout << "TEST turn left: \n";
        std::cout << "TEST turn left with high maneuvrability and low grab: \n";

        std::cout << "OK\n";
    }

    void testTurnLeftWithHighManeuverabilityAndHighGrab(){
        std::cout << "TEST turn left with high maneuvrability and high grab: \n";

        std::cout << "OK\n";
    }

    void testCrashesWithAnotherCarLosesHealth(){}

    void testExplodesWhenHealthIn0(){
        std::cout << "TEST explodes when health is 0: \n";

        std::cout << "OK\n";
    }

};

#endif //MICROMACHINES_CARTEST_H
