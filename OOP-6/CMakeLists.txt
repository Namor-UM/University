cmake_minimum_required(VERSION 3.20)
project(OOP_6)

set(CMAKE_CXX_STANDARD 14)
set(BASE64_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base64/include)

add_subdirectory(base64)
add_subdirectory(tests)

include_directories(${BASE64_INCLUDE_DIR})
add_executable(main main.cpp)
target_link_libraries(main base64)
