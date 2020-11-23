cmake_minimum_required(VERSION 3.10)

# set the project name
project(coverage_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_library(add STATIC src/add.cpp)

# unit test
add_subdirectory(test)
