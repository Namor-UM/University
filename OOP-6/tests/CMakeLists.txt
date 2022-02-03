add_subdirectory(googletest)

add_executable(tests tests.cpp)
include_directories(${BASE_INCLUDE_DIR})

target_link_libraries(tests Base64 gtest gtest_main)