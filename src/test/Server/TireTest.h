#ifndef MICROMACHINES_TIRETEST_H
#define MICROMACHINES_TIRETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "src/Server/Model/Car/Tire.h"

class TireTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TireTest );
    CPPUNIT_TEST(testAtFirstHasNoVelocity);
    CPPUNIT_TEST(testMovingForward);
CPPUNIT_TEST_SUITE_END();

private:
    b2World* world;
    Tire* tire;

public:
    void setUp(){
        b2Vec2 gravity = b2Vec2(0,0);
        world = new b2World(gravity);
        tire = new Tire(world, 100, -20, 75);
    }

    void tearDown(){
        delete tire;
        delete world;
    }

    void testAtFirstHasNoVelocity(){
        std::cout << "TEST at first has no velocity:\n";

        world->Step( 1/30.0, 8, 3);
        CPPUNIT_ASSERT(tire->getForwardVelocity().x == 0);
        CPPUNIT_ASSERT(tire->getForwardVelocity().y == 0);

        std::cout << "OK\n";
    }

    void testMovingForward(){
        std::cout << "TIRE TESTS: \n";
        std::cout << "TEST moving forward:\n";

        tire->updateFriction();
        //tire->updateDrive(TDC_UP);
        world->Step( 1/30.0, 8, 3);
        CPPUNIT_ASSERT(tire->getForwardVelocity().x == 0);
        CPPUNIT_ASSERT(tire->getForwardVelocity().y > 0);

        std::cout << "OK\n";
    }

};

#endif //MICROMACHINES_TIRETEST_H
