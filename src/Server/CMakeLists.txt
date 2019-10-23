cmake_minimum_required(VERSION 3.10)
project(Micromachines)

include_directories(../..)

add_library(mm_server_library
        Model/Car.cpp
        Model/World.cpp Model/Game.cpp Model/Game.h)

target_link_libraries(mm_server_library Box2D)