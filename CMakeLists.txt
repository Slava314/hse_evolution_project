cmake_minimum_required(VERSION 3.17)
project(evolution_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

#add_compile_options(-O3 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self
#        -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body
#        -Wmissing-field-initializers -Wctor-dtor-privacy -Wnon-virtual-dtor
#        -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++)

add_compile_options(-O3)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)


list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTOS server/server.proto)

set(PROTO_SRC_DIR proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})


include_directories(include)

include(CMakeRC.cmake)

cmrc_add_resource_library(resources WHENCE resources resources/times.ttf)

add_executable(${PROJECT_NAME}
        source/button.cpp
        source/animal.cpp
        source/deck.cpp
        source/game.cpp
        source/player.cpp
        source/game_window.cpp
        source/view.cpp
        source/main.cpp
        source/development_phase.cpp
        source/feeding_phase.cpp
        source/cards.cpp
        source/start_windows.cpp
        source/properties.cpp
        source/text_field.cpp source/settings.cpp
        ${PROTO_SRCS}
        ${GRPC_SRCS})

include_directories(include)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SFML_DIR "SFML-2.5.1-macos-clang/include/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

#set (resources "${CMAKE_SOURCE_DIR}/resources")
#set (resources_target "${CMAKE_CURRENT_BINARY_DIR}/resources")
#add_custom_command(
#        TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E create_symlink ${resources} ${resources_target}
#        COMMENT "symbolic link resources folder from ${resources} => ${resources_target}"
#)

target_link_libraries(evolution_project sfml-graphics sfml-audio resources gRPC::grpc++_reflection
        protobuf::libprotobuf)



#target_link_libraries(evolution_project PRIVATE resources)
