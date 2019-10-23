cmake_minimum_required(VERSION 3.10)
project(Micromachines)

include_directories(../..)

add_library(mm_server_library
        Model/Car/Car.cpp
        Model/World.cpp
        Model/Game.cpp
        Model/Input.h
        Model/Car/CarState.h
        Model/Car/AcceleratingState.h
        Model/Car/WithoutAcceleratingState.h
        Model/Car/NegAcceleratingState.h)

target_link_libraries(mm_server_library Box2D)