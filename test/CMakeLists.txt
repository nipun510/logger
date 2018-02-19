cmake_minimum_required (VERSION 2.6)

add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_link_libraries (test LINK_PUBLIC logger)
