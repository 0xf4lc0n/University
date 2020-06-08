cmake_minimum_required(VERSION 3.16)
project(backtracking_algorithm)

set(CMAKE_CXX_STANDARD 20)

include_directories(../libs/backtracking)

set(BACKTRACKING
        ../libs/backtracking/knapsack.h
        ../libs/backtracking/knapsack.cpp
   )

set(SOURCES main.cpp ${BACKTRACKING})

add_executable(backtracking_algorithm ${SOURCES})
