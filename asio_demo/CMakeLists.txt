cmake_minimum_required(VERSION 3.10)

# set the project name
project(asio_demo)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
include (gcovr)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(asio-1.16.1/include)

add_definitions(-DASIO_STANDALONE)


# add the executable
add_executable(asio_demo src/asio_demo.cpp)
target_link_libraries(asio_demo ${CMAKE_THREAD_LIBS_INIT})

# unit test
add_subdirectory(test)
