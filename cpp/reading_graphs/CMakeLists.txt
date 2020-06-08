cmake_minimum_required(VERSION 3.15)
project(reading_graphs)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/graphs)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
        )

set(GRAPHS
        ../libs/graphs/List.h
        ../libs/graphs/List.cpp
        ../libs/graphs/auxiliary.h
        ../libs/graphs/auxiliary.cpp
   )

add_library(input_sanitization SHARED ${INPUT_SANITIZATION})
add_library(graphs SHARED ${GRAPHS})

add_executable(directed_graph reading_directed_graph.cpp)
target_link_libraries(directed_graph input_sanitization graphs)

add_executable(non_directed_graph reading_non_directed_graph.cpp)
target_link_libraries(non_directed_graph input_sanitization graphs)