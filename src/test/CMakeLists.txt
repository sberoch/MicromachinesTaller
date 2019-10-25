cmake_minimum_required(VERSION 3.1.0)
project(Micromachines)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -pedantic-errors")

include_directories(../..)

add_executable(tests
        testMain.cpp
        Server/CarTest.h
        Server/TireTest.h)

target_link_libraries(tests cppunit mm_server_library)

