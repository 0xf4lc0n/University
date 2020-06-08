cmake_minimum_required(VERSION 3.15)
project(recursion_and_inversion)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/recursion)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
   )

set(RECURSION
        ../libs/recursion/recursion_and_merge.h
        ../libs/recursion/recursion_and_merge.cpp
   )

add_library(input_sanitization SHARED ${INPUT_SANITIZATION})
add_library(recursion_inversion SHARED ${RECURSION})

add_executable(recursion recursion.cpp)
target_link_libraries(recursion input_sanitization recursion_inversion)

add_executable(inversion inversion.cpp)
target_link_libraries(inversion input_sanitization recursion_inversion)
