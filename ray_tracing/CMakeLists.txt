cmake_minimum_required (VERSION 3.9)

set (CMAKE_C_COMPILER               "clang-cl")
set (CMAKE_C_FLAGS                  "-Wall")
set (CMAKE_C_FLAGS_DEBUG            "/Debug")
set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG")
set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 /Debug")
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_COMPILER             "clang-cl")
set (CMAKE_CXX_FLAGS                "-Wall -Xclang -std=gnu++14")
set (CMAKE_CXX_FLAGS_DEBUG          "/Debug")
set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 /Debug")


project(RayTracing)

include_directories("${PROJECT_SOURCE_DIR}/includes")

add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter03)