cmake_minimum_required(VERSION 3.21)
enable_language(CXX)
project(aoc23 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(executables d1)
set(executables d2)

find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

foreach(executable ${executables})
    add_executable(${executable} "${executable}/main.cxx")
endforeach()

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -checks=*;
    -header-filter=.*;
)