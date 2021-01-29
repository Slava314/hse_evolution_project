cmake_minimum_required(VERSION 3.17)
project(evolution_project)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wshadow)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(evolution_project main.cpp)

target_link_libraries(evolution_project sfml-graphics sfml-audio)