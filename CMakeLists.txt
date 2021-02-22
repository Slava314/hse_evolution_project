cmake_minimum_required(VERSION 3.17)
project(evolution_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
add_compile_options(-O3 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self
        -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body
        -Wmissing-field-initializers -Wctor-dtor-privacy -Wnon-virtual-dtor
        -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME}
        source/main.cpp
        source/button.cpp
        source/animal.cpp
        source/board.cpp
        source/deck.cpp
        source/game.cpp
        source/player.cpp)


include_directories(include)

target_link_libraries(evolution_project sfml-graphics sfml-audio)