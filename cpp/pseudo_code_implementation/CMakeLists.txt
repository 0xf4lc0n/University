cmake_minimum_required(VERSION 3.15)
project(pseudo_code)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/pseudo_code_impl)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
        )

set(SET_MANIP
        ../libs/pseudo_code_impl/set_manipulation.h
        ../libs/pseudo_code_impl/set_manipulation.cpp
   )

add_library(input_sanitization SHARED ${INPUT_SANITIZATION})

set(SOURCES1 0x1.cpp ${SET_MANIP})
set(SOURCES2 0x2.cpp ${SET_MANIP})
set(SOURCES3 0x3.cpp ${SET_MANIP})

add_executable(0x1 ${SOURCES1})
target_link_libraries(0x1 input_sanitization)

add_executable(0x2 ${SOURCES2})
target_link_libraries(0x2 input_sanitization)

add_executable(0x3 ${SOURCES3})
target_link_libraries(0x3 input_sanitization)