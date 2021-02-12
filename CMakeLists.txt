cmake_minimum_required(VERSION 3.17)
project(evolution_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
add_compile_options(-Wall -Wextra -Wshadow)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(evolution_project source/main.cpp source/Animal.cpp source/Board.cpp source/Deck.cpp source/Game.cpp source/Player.cpp)

include_directories(include)

target_link_libraries(evolution_project sfml-graphics sfml-audio)
#target_link_libraries(try sfml-graphics sfml-audio)

