cmake_minimum_required(VERSION 3.1.0)
project(Micromachines)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Werror -pedantic -pthread")

message("[INFO] Cargando fuentes del servidor")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Server/*.cpp" "src/Server/*.h")

message("[INFO] Cargando fuentes compartidos")
file(GLOB_RECURSE LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Common/*.cpp" "src/Common/*.h")

message("[INFO] Cargando fuentes del cliente")
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Client/*.cpp" "src/Client/*.h")

#Agregar en add_executable ${LIBS_SOURCES} cuando se pongan cosas en Common

add_executable(mm_client ${CLIENT_SOURCES})
target_link_libraries(mm_client SDL2 SDL2_image SDL2_mixer SDL2_ttf)

add_executable(mm_server ${SERVER_SOURCES})
target_link_libraries(mm_server)

install(FILES assets/fondo.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/pista_recta.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/pista_curva.png DESTINATION ${CMAKE_BINARY_DIR})
