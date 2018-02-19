cmake_minimum_required (VERSION 2.6)
set(Logger_VERSION_MAJOR 1)
set(Logger_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(logger SHARED ${PROJECT_SOURCE_DIR}/src/logger.cpp)
target_include_directories (logger PUBLIC ${PROJECT_SOURCE_DIR}/include)



add_subdirectory(test)
