#ifndef MICROMACHINES_CARTEST_H
#define MICROMACHINES_CARTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/Server/Model/Car.h"

class CarTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( CarTest );
        CPPUNIT_TEST( testCreateCarInTheExitLine );
        CPPUNIT_TEST( testCreateMultipleCarsInTheExitLineOneNextToEachOther );
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
    float car_x_init = 0;//Ver cuales son las posiciones correctas en la pantalla.
    float car_y_init = 0;

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

    void testCreateCarInTheExitLine(){
        std::cout << "TESTS CAR\n";

        std::cout << "TEST create car in the middle of the track: \n";

        //CPPUNIT_ASSERT(car1->x == car_x_init);
        //CPPUNIT_ASSERT(car1->y == car_y_init);
        std::cout << "OK\n";
    }

    void testCreateMultipleCarsInTheExitLineOneNextToEachOther(){
        std::cout << "TEST create multiple cars in the middle of the track: \n";

        //CPPUNIT_ASSERT(car1->x == car_x_init);
        //CPPUNIT_ASSERT(car1->y == car_y_init);

        //TODO: ver distancias entre autos
        //CPPUNIT_ASSERT(car2->x == car_x_init + 0.1);
        //CPPUNIT_ASSERT(car2->y == car_y_init);

        //CPPUNIT_ASSERT(car3->x == car_x_init + 0.2);
        //CPPUNIT_ASSERT(car3->y == car_y_init);
        std::cout << "OK\n";
    }

    void testStart(){

    }

    void testIncreaseSpeed(){

    }

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
