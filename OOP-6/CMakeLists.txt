cmake_minimum_required(VERSION 3.20)
project(OOP_6)

set(CMAKE_CXX_STANDARD 14)
set(BASE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Base64/include)

add_subdirectory(Base64)
add_subdirectory(tests)

include_directories(${BASE_INCLUDE_DIR})
add_executable(main main.cpp)
target_link_libraries(main Base64)
