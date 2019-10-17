cmake_minimum_required(VERSION 3.1.0)
project(Micromachines)

# Quito los flags porque no compila Box2D sino, los warnings lo rebotan
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Werror -pedantic -pthread")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline -std=c++11 -pthread")
set (CMAKE_MODULE_PATH  "/home/miki_mustard/Desktop/Facultad/Taller/MicromachinesTaller/cmake-build-debug/CMakeFiles/3.14.5")

message("[INFO] Agregando Box2D")
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
set(BOX2D_VERSION 2.3.0)

add_subdirectory(Box2D)

message("[INFO] Cargando fuentes del servidor")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Server/*.cpp" "src/Server/*.h")

message("[INFO] Cargando fuentes compartidos")
file(GLOB_RECURSE LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Common/*.cpp" "src/Common/*.h")

message("[INFO] Cargando fuentes del cliente")
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Client/*.cpp" "src/Client/*.h")

#Agregar en add_executable ${LIBS_SOURCES} cuando se pongan cosas en Common

add_executable(mm_client ${CLIENT_SOURCES})
target_link_libraries(mm_client SDL2 SDL2_image SDL2_mixer SDL2_ttf)

add_subdirectory(src/Server)
#add_executable(mm_server ${SERVER_SOURCES})
add_executable(mm_server src/Server/serverMain.cpp)
target_link_libraries(mm_server mm_server_library)

install(FILES assets/fondo.png DESTINATION ${CMAKE_BINARY_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(mm_client ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})



