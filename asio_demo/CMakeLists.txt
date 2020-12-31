cmake_minimum_required(VERSION 3.13)

# set the project name
project(asio_demo)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
include (gcovr)

find_package(Threads REQUIRED)

# cpp options
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# target
set(TARGET_NAME asio_demo)

# add the executable
add_executable(${TARGET_NAME} src/asio_demo.cpp)

# include directories
target_include_directories(${TARGET_NAME} PUBLIC asio-1.16.1/include)

# preprocessor
target_compile_definitions(${TARGET_NAME} PUBLIC ASIO_STANDALONE)

# gcc feature
set(GCC_UNDEFINED_FLAG "-fsanitize=undefined")

# compile options
target_compile_options(${TARGET_NAME} PUBLIC ${GCC_UNDEFINED_FLAG})

# link options
target_link_options(${TARGET_NAME} PUBLIC ${GCC_UNDEFINED_FLAG})

# link dependency
target_link_libraries(${TARGET_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})

# unit test
add_subdirectory(test)