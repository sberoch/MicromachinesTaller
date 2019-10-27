#ifndef MICROMACHINES_TESTCAR_H
#define MICROMACHINES_TESTCAR_H

#define DEGTORAD 0.0174532925199432957f

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

public:
    void setUp(){
        b2Vec2 gravity(0, 0);
        world = new b2World(gravity);

        b2BodyDef _carBodyDef;
        _carBodyDef.type = b2_dynamicBody;
        _carBodyDef.position.Set(15, 7);
        _carBodyDef.angle = 180 * DEGTORAD;

        b2Body* carBody = world->CreateBody(&_carBodyDef);

        car1 = new Car(carBody);
    }

    void tearDown(){
        //delete car1;
    }

    void testCreateCarInTheExitLine(){
        std::cout << "TESTS CAR\n";

        std::cout << "TEST create car in the exit line: \n";

        CPPUNIT_ASSERT(car1->x() == _car_x_init);
        CPPUNIT_ASSERT(car1->y() == _car_y_init);
        CPPUNIT_ASSERT(car1->speed() == 0);
        //See how to check state
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

        car1->handleInput(PRESS_UP);
        car1->update();
        world->Step(1/30.0, 8, 3);
        CPPUNIT_ASSERT(car1->speed() > 0);

        std::cout << "OK\n";
    }

    void testPressDownKey(){
        std::cout << "TEST press down key: \n";

        car1->handleInput(PRESS_DOWN);
        car1->update();
        world->Step(1/30.0, 8, 3);
        CPPUNIT_ASSERT(car1->speed() < 0);

        std::cout << "OK\n";
    }

    void testPressNoKey(){
        std::cout << "TEST press no key: \n";

        car1->handleInput(PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        CPPUNIT_ASSERT(car1->speed() == 0);

        std::cout << "OK\n";
    }

    void testPressUpThenNoKey(){
        std::cout << "TEST press up and then no key: \n";
        //Floor?
        b2Body* floor;
        b2PolygonShape polygonShape;
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.density = 1;
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(_car_x_init, _car_y_init);

        polygonShape.SetAsBox(10,10);
        floor = world->CreateBody(&myBodyDef);
        floor->CreateFixture(&myFixtureDef);

        car1->handleInput(PRESS_UP);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();

        car1->handleInput(PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        float intermidiate_speed = car1->speed();
        CPPUNIT_ASSERT(car1->speed() > 0);

        std::cout << "OK\n";
        std::cout << "Loses velocity in time\n";
        car1->handleInput(PRESS_NONE);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        CPPUNIT_ASSERT(car1->speed() < intermidiate_speed);

        std::cout << "OK\n";
        std::cout << "Eventually reaches zero speed\n";
        car1->handleInput(PRESS_NONE);
		car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        CPPUNIT_ASSERT(car1->speed() == 0);        

        std::cout << "OK\n";
    }

    void testPressUpThenDownKey(){
        std::cout << "TEST press up and then down key: \n";

        car1->handleInput(PRESS_UP);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();

        car1->handleInput(PRESS_DOWN);
        car1->update();
        world->Step(1/30.0, 8, 3);
        world->ClearForces();
        CPPUNIT_ASSERT(car1->speed() == 0);

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

    void testExplodesWhenHealthIn0(){
        std::cout << "TEST explodes when health is 0: \n";

        std::cout << "OK\n";
    }

};

#endif //MICROMACHINES_CARTEST_H
