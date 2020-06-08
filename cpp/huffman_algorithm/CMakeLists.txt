cmake_minimum_required(VERSION 3.16)
project(huffman_algorithm)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/huffman)
include_directories(../libs/exceptions)

set(HUFFMAN
    ../libs/huffman/huffman.tcc
    ../libs/huffman/node.tcc
   )

set(EXCEPTION
    ../libs/exceptions/exceptions.h
    ../libs/exceptions/exceptions.cpp
   )

set(SOURCES main.cpp ${HUFFMAN} ${EXCEPTION})

add_executable(huffman_algorithm ${SOURCES})