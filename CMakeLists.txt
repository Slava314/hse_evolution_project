cmake_minimum_required(VERSION 3.17)
project(evolution_project)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wshadow)

add_executable(main main.cpp)