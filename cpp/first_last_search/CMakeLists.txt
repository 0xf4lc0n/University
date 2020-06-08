cmake_minimum_required(VERSION 3.15)
project(first_last_search)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/searching)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
   )

set(SEARCHING
        ../libs/searching/searching.h
        ../libs/searching/searching.cpp
   )

add_library(input_sanitization STATIC ${INPUT_SANITIZATION})

set(SOURCES main.cpp ${SEARCHING})

add_executable(first_last_search ${SOURCES})
target_link_libraries(first_last_search input_sanitization)