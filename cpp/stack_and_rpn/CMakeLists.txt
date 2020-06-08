cmake_minimum_required(VERSION 3.15)
project(rps_stack)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/stack_and_rpn)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
   )

set(STACK_AND_RPN
        ../libs/stack_and_rpn/RPN.h
        ../libs/stack_and_rpn/RPN.cpp
        ../libs/stack_and_rpn/Stack.tcc
   )

add_library(input_sanitization SHARED ${INPUT_SANITIZATION})
add_library(stack_and_rpn SHARED ${STACK_AND_RPN})

add_executable(stack_drive stack_drive.cpp)
target_link_libraries(stack_drive input_sanitization stack_and_rpn)

add_executable(rpn_drive rpn_drive.cpp)
target_link_libraries(rpn_drive input_sanitization stack_and_rpn)