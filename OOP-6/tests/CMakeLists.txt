add_subdirectory(googletest)

add_executable(tests tests.cpp)
include_directories(${BASE64_INCLUDE_DIR})

target_link_libraries(tests base64 gtest gtest_main)