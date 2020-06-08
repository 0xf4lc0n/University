cmake_minimum_required(VERSION 3.16)
project(Lab9)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/backpack)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
   )

set(BACKPACK
        ../libs/backpack/backpack_problem.cpp
        ../libs/backpack/backpack_problem.tcc
        ../libs/backpack/subject.tcc
   )

add_library(input_sanitization SHARED ${INPUT_SANITIZATION})
add_library(backpack SHARED ${BACKPACK})

add_executable(dynamic_approach dynamic_programming_approach.cpp)
target_link_libraries(dynamic_approach input_sanitization backpack)

add_executable(recursive_approach recursive_approach.cpp)
target_link_libraries(recursive_approach input_sanitization backpack)