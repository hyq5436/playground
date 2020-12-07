cmake_minimum_required(VERSION 3.10)

# set the project name
project(gmock_demo)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# unit test
add_subdirectory(test)
