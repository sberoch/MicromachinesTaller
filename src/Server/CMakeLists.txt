cmake_minimum_required(VERSION 3.10)
project(Micromachines)

include_directories(../..)

add_library(mm_server_library
        Model/Car/Car.cpp
        Model/World.cpp
        Model/Game.cpp
        Model/Input.h
        Model/Car/Turning/CarTurningState.h Model/Car/Turning/TurningLeftState.h Model/Car/Turning/NotTurningState.h Model/Car/Turning/TurningRightState.h Model/Track.cpp Model/Track.h Model/Car/Tire.cpp Model/Car/Tire.h Model/ContactListener.cpp Model/ContactListener.h Model/FixtureUserData.h)

target_link_libraries(mm_server_library Box2D)