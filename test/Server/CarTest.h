#ifndef MICROMACHINES_CARTEST_H
#define MICROMACHINES_CARTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CarTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( CarTest );
        CPPUNIT_TEST( testStart );
        CPPUNIT_TEST( testIncreaseSpeed );
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
    Car *car1, *car2, *car3;
public:
    void setUp(){
        car1 = new Car();
        car2 = new Car();
        car3 = new Car();
    }

    void tearDown(){
        delete car1;
        delete car2;
        delete car3;
    }

    void testStart(){}

    void testIncreaseSpeed(){}

    void testDecreaseSpeed(){}

    void testTurnRight(){}

    void testTurnRightWithLowManeuverabilityAndLowGrab(){}

    void testTurnRightWithLowManeuverabilityAndHighGrab(){}

    void testTurnRightWithHighManeuverabilityAndLowGrab(){}

    void testTurnRightWithHighManeuverabilityAndHighGrab(){}

    void testTurnLeftWithLowManeuverabilityAndLowGrab(){}

    void testTurnLeftWithLowManeuverabilityAndHighGrab(){}

    void testTurnLeftWithHighManeuverabilityAndLowGrab(){}

    void testTurnLeftWithHighManeuverabilityAndHighGrab(){}

    void testExplodesWhenHealthIn0(){}

};

#endif //MICROMACHINES_CARTEST_H
