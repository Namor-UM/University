cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(OOP-4)

# или console, или file
set(OUT console)

add_executable(main main.cpp)

add_library(print SHARED print_ostream.cpp print_${OUT}.cpp)

add_library(matrix STATIC matrix.cpp)

target_link_libraries(main PRIVATE print matrix)
