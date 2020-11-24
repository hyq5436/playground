cmake_minimum_required(VERSION 3.10)

# set the project name
project(external_proj_demo)
include(ExternalProject)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include_directories(asio-1.16.1/include)

#add_definitions(-DASIO_STANDALONE)


# add the executable
#add_executable(asio_demo src/asio_demo.cpp)
#target_link_libraries(asio_demo ${CMAKE_THREAD_LIBS_INIT})

# unit test
#add_subdirectory(test)

set(QWT_PATH ${CMAKE_SOURCE_DIR}/qwt-6.1.4)
set(QMAKE_PATH /home/page/QT/Qt5.14.2/5.14.2/gcc_64/bin/qmake)
ExternalProject_Add(qwt_build
	DOWNLOAD_COMMAND ""
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	SOURCE_DIR ${QWT_PATH}
	CONFIGURE_COMMAND ${QMAKE_PATH} ${QWT_PATH}/qwt.pro
	BUILD_COMMAND make
	INSTALL_COMMAND ""
)

