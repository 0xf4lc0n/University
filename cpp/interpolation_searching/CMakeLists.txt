cmake_minimum_required(VERSION 3.15)
project(interpolation_searching)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/input_sanitization)
include_directories(../libs/interpolation_searching)

set(INPUT_SANITIZATION
        ../libs/input_sanitization/input_sanitization.h
        ../libs/input_sanitization/input_sanitization.cpp
        ../libs/input_sanitization/input_sanitization.tcc
   )

set(INTERPOLATION_SEARCH
        ../libs/interpolation_searching/awesome_cut_library.h
        ../libs/interpolation_searching/awesome_cut_library.cpp
        ../libs/interpolation_searching/awesome_cut_library.tcc
   )

add_library(input_sanitization STATIC ${INPUT_SANITIZATION})
set(SOURCES i_search_drive.cpp ${INPUT_SANITIZATION} ${INTERPOLATION_SEARCH})

add_executable(interpolation_searching ${SOURCES})
target_link_libraries(interpolation_searching input_sanitization)