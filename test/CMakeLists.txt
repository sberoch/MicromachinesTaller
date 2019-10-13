cmake_minimum_required(VERSION 3.1.0)
project(Micromachines)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Werror -pedantic -pthread")

add_executable(tests
        testMain.cpp
        Server/CarTest.h)

target_link_libraries(tests cppunit):