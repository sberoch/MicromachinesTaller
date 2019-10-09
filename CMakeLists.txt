cmake_minimum_required(VERSION 3.1.0)
project(Portal)

# Quito los flags porque no compila Box2D sino, los warnings lo rebotan
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Werror -pedantic -pthread")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline -std=c++11 -pthread")

message("[INFO] Agregando '${CMAKE_SOURCE_DIR}/src/3rd-party' como directorio de includes")
include_directories(${CMAKE_SOURCE_DIR}/src/3rd-party)

message("[INFO] Agregando Box2D como libreria")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/3rd-party/Box2D/*.cpp" "src/3rd-party/Box2D/*.h")
add_library(Box2D STATIC ${BOX2D_SOURCES})

#message("[INFO] Agregando yaml-cpp como libreria")
#file(GLOB_RECURSE YAMLCPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/3rd-party/yaml-cpp/*.cpp" "src/3rd-party/yaml-cpp/*.h")
#add_library(yamlcpp STATIC ${YAMLCPP_SOURCES})

message("[INFO] Cargando fuentes del servidor")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*.cpp" "src/server/*.h")

message("[INFO] Cargando fuentes compartidos")
file(GLOB_RECURSE LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Common/*.cpp" "src/Common/*.h")

message("[INFO] Cargando fuentes del cliente")
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Cliente/*.cpp" "src/Cliente/*.h")

add_executable(portal_client ${CLIENT_SOURCES}  ${LIBS_SOURCES})
target_link_libraries(portal_client SDL2 SDL2_image SDL2_mixer SDL2_ttf yaml-cpp)

add_executable(portal_server ${SERVER_SOURCES} ${LIBS_SOURCES})
target_link_libraries(portal_server Box2D yaml-cpp)

install(FILES assets/emisor_receptor.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/bloque_metal_diag.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/boton_menu.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/fondo.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/chell.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/miscelanea.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/puertas.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/efectos.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/pin.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/cake.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/portales.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/menu.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/sala.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/escenario.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/musica_fondo.mp3 DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/disparo_portal.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/salto.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/muerte.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/boton.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/puerta.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/portal.ttf DESTINATION ${CMAKE_BINARY_DIR})

