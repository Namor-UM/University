add_subdirectory(googletest)

add_executable(tests tests.cpp)
include_directories(${MATRIX_INCLUDE_DIR})

target_link_libraries(tests matrix gtest gtest_main)
