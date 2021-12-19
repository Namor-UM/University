cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(OOP-4)

add_executable(main main.cpp)

add_library(print SHARED print_ostream.cpp print_console.cpp)

add_library(matrix STATIC matrix.cpp)

target_link_libraries(main PRIVATE print matrix)