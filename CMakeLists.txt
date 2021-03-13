cmake_minimum_required(VERSION 3.17)
project(Echoes)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Echoes main.cpp menu.h menuin.h cmake-build-debug/images/asf.cpp cmake-build-debug/images/asf.h)

target_link_libraries(Echoes sfml-graphics sfml-audio)

