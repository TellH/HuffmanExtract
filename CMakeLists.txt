cmake_minimum_required(VERSION 3.5)
project(Huffman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp HuffmanTree.h HuffmanTree.cpp Heap.cpp Heap.h example.cpp )
add_executable(Huffman ${SOURCE_FILES})