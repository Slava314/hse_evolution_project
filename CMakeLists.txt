cmake_minimum_required(VERSION 3.17)
project(evolution_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
#add_compile_options(-O3 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self
#        -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body
#        -Wmissing-field-initializers -Wctor-dtor-privacy -Wnon-virtual-dtor
#        -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME}
        source/main.cpp
        source/button.cpp
        source/animal.cpp
        source/board.cpp
        source/deck.cpp
        source/game.cpp
        source/player.cpp
        source/window.cpp
        source/view.cpp
        source/phase.cpp)

include_directories(include)

set (resources "${CMAKE_SOURCE_DIR}/resources")
set (resources_target "${CMAKE_CURRENT_BINARY_DIR}/resources")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${resources} ${resources_target}
        COMMENT "symbolic link resources folder from ${resources} => ${resources_target}"
)

#file(GLOB resources resources/*)
#fle(COPY ${resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)

target_link_libraries(evolution_project sfml-graphics sfml-audio)