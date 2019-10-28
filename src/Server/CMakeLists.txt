cmake_minimum_required(VERSION 3.10)
project(Micromachines)

include_directories(..)
include_directories(../..)

add_library(mm_server_library
        Model/Car/Car.cpp
        Model/World.cpp
        Model/Game.cpp
        Model/Input.h
        Model/Track.cpp
        Model/Car/Tire.cpp
        Model/ContactListener.cpp
        Model/FixtureUserData.h)

target_link_libraries(mm_server_library Box2D)