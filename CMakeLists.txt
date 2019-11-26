cmake_minimum_required(VERSION 3.1.0)
project(Micromachines)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline -std=c++11 -pthread")
set (CMAKE_SHARED_LINKER_FLAGS "-ldl")

find_package(Lua REQUIRED)

message("Variables:\n")
message("LUA_FOUND: ${LUA_FOUND}")
message("LUA_LIBRARIES: ${LUA_INCLUDE_DIR}")
message("LUA_INCLUDE_DIR: ${LUA_INCLUDE_DIR}")
message("LUA_VERSION_STRING: ${LUA_VERSION_STRING}")
message("LUA_VERSION_MAJOR: ${LUA_VERSION_MAJOR}")
message("LUA_VERSION_MINOR: ${LUA_VERSION_MINOR}")
message("LUA_VERSION_PATCH: ${LUA_VERSION_PATCH}")

include_directories(${LUA_INCLUDE_DIR})

message("[INFO] Agregando '${CMAKE_SOURCE_DIR}/src/3rd-party' como directorio de includes")
include_directories(${CMAKE_SOURCE_DIR}/src/3rd-party)

message("[INFO] Agregando Box2D como libreria")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/3rd-party/Box2D/*.cpp" "src/3rd-party/Box2D/*.h")
add_library(Box2D STATIC ${BOX2D_SOURCES})

message("[INFO] Cargando fuentes del servidor")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Server/*.cpp" "src/Server/*.h")

message("[INFO] Cargando fuentes compartidos")
file(GLOB_RECURSE COMMON_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Common/*.cpp" "src/Common/*.h" "src/Common/*.hpp")

message("[INFO] Cargando fuentes del cliente")
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Client/*.cpp" "src/Client/*.h")

add_executable(mm_client ${CLIENT_SOURCES} ${COMMON_SOURCES})
target_link_libraries(mm_client SDL2 SDL2_image SDL2_mixer lua5.3)

add_executable(mm_server ${SERVER_SOURCES} ${COMMON_SOURCES})
target_link_libraries(mm_server Box2D ${CMAKE_DL_LIBS})

message("[INFO] Installation")
INSTALL(TARGETS mm_client mm_server DESTINATION /usr/bin)
INSTALL(DIRECTORY assets DESTINATION /var/Micromachines)
INSTALL(FILES src/mods/libs.txt DESTINATION /etc/Micromachines)

