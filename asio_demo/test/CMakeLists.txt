cmake_minimum_required(VERSION 3.10)

enable_testing()
find_package(GTest REQUIRED)

# thread
find_package(Threads REQUIRED)

# cpp options
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# gcc feature
set(GCC_UNDEFINED_FLAG "-fsanitize=undefined")
set(CMAKE_CXX_FLAGS_COVERAGE "-g;-O0;--coverage")

# set target
set(TEST_EXECUTOR tests)
aux_source_directory(. TEST_FILES)
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/printer.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/printer2.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/server.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server.h)
add_executable(${TEST_EXECUTOR} ${TEST_FILES})

# include directories
target_include_directories(${TEST_EXECUTOR}
    PUBLIC
        ${GTEST_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/asio-1.16.1/include)

# compile options
target_compile_options(${TEST_EXECUTOR} PUBLIC ${GCC_UNDEFINED_FLAG} ${CMAKE_CXX_FLAGS_COVERAGE})

# link options
target_link_options(${TEST_EXECUTOR} PUBLIC ${GCC_UNDEFINED_FLAG} --coverage -lgcov)

# link dependency
target_link_libraries(${TEST_EXECUTOR} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# gtest
gtest_discover_tests(${TEST_EXECUTOR})

#[[ run test auto
add_custom_command(TARGET tests
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure
		   COMMAND echo "Hello world!")
]]
