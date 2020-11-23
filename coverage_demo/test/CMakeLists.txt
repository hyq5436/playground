cmake_minimum_required(VERSION 3.10)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
include (gcovr)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Threads REQUIRED)

aux_source_directory(. TEST_FILES)
add_executable(tests ${TEST_FILES})

set(CMAKE_CXX_FLAGS_COVERAGE "-g -O0 --coverage")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -lgcov")


include_directories(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(tests add ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
gtest_discover_tests(tests)

add_custom_command(TARGET tests
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure)
