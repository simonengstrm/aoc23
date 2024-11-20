cmake_minimum_required(VERSION 3.9)
project(aoc23 LANGUAGES CXX)
enable_language(CXX)

# Set compiler to clang++
set(CMAKE_CXX_COMPILER clang++)

#Echo current compiler
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(executables d1 d2 d3 d4)

foreach(executable ${executables})
    add_executable(${executable} "${executable}/main.cxx")
    include_directories(${executable})
endforeach()