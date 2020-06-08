cmake_minimum_required(VERSION 3.16)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/generators)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.tcc
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
   )

set(GENERATORS
        ../libs/generators/generators.tcc
   )

add_library(input_sanitization STATIC ${INPUT_SANITIZATION})

add_executable(generators generators_drive.cpp ${GENERATORS})
target_link_libraries(generators input_sanitization)
