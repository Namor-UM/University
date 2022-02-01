cmake_minimum_required(VERSION 3.20)
project(OOP_5)

set(CMAKE_CXX_STANDARD 14)
set(MATRIX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/matrix/include)

add_subdirectory(matrix)
add_subdirectory(tests)

include_directories(${MATRIX_INCLUDE_DIR})
add_executable(main main.cpp)
target_link_libraries(main matrix)
