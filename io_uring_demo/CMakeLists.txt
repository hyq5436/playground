cmake_minimum_required(VERSION 3.0.0)
project(io_uring_demo VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

add_executable(io_uring_demo io_uring_demo.cpp)
target_link_libraries(io_uring_demo PUBLIC uring)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
