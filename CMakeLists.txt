cmake_minimum_required(VERSION 3.1.0)
project(Micromachines)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Werror -pedantic -pthread")

message("[INFO] Cargando fuentes del servidor")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Server/*.cpp" "src/Server/*.h")

message("[INFO] Cargando fuentes compartidos")
file(GLOB_RECURSE COMMON_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Common/*.cpp" "src/Common/*.h" "src/Common/*.hpp")

message("[INFO] Cargando fuentes del cliente")
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Client/*.cpp" "src/Client/*.h")

add_executable(mm_client ${CLIENT_SOURCES} ${COMMON_SOURCES})
target_link_libraries(mm_client SDL2 SDL2_image SDL2_mixer SDL2_ttf)


add_executable(mm_server ${SERVER_SOURCES} ${COMMON_SOURCES})
target_link_libraries(mm_server)

install(FILES assets/scene.json DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/car_1.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/car_2.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/car_3.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/car_4.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/background.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/straight_track.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/rock.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/curve_track.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/powerups.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/oil.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/mud.png DESTINATION ${CMAKE_BINARY_DIR})

