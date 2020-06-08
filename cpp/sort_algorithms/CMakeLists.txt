cmake_minimum_required(VERSION 3.16)
project(sort_algorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(../libs/input_sanitization)
include_directories(../libs/c_array)
include_directories(../libs/exceptions)
include_directories(../libs/stack_size)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.tcc
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
    )

set(SORT_ARRAYS
        ../libs/c_array/c_sort_array.h
        ../libs/c_array/c_array.h
   )

set(EXCEPTIONS
        ../libs/exceptions/exceptions.cpp
        ../libs/exceptions/exceptions.h
   )

set(STACK
        ../libs/stack_size/stack_size.cpp
        ../libs/stack_size/stack_size.h
   )

add_library(input_sanitization STATIC ${INPUT_SANITIZATION})
set(SOURCES main.cpp ${SORT_ARRAYS} ${EXCEPTIONS} ${STACK})

add_executable(sort_algorithms ${SOURCES})
target_link_libraries(sort_algorithms input_sanitization)