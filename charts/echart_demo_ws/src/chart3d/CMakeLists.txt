cmake_minimum_required(VERSION 3.0.2)
project(chart3d LANGUAGES CXX)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rviz
  std_msgs
)

# config CEF
set(CEF_ROOT "/home/page/third_party/cef_binary_85.3.5+gd7ff358+chromium-85.0.4183.102_linux64")
# set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")
find_package(CEF REQUIRED)

## QT support
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)
set(QT_LIBRARIES Qt5::Widgets Qt5::Sql)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES chart3d
  CATKIN_DEPENDS roscpp rviz std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CEF_INCLUDE_PATH}
  ${CMAKE_CURRENT_BINARY_DIR}/..
)

## Declare a C++ library
add_library(${PROJECT_NAME}
  src/chart3d.h 
  src/chart3d.cpp 
  src/browser_setting.cc 
  src/browser_setting.h 
  src/bubble.cc 
  src/bubble.h 
  src/profile.cc 
  src/profile.h 
  src/sql.cc 
  src/sql.h 
  src/util.cc 
  src/util.h 
  src/util_linux.cc 
  src/cef/cef.cc 
  src/cef/cef.h 
  src/cef/cef_app_handler.cc 
  src/cef/cef_app_handler.h 
  src/cef/cef_base.h 
  src/cef/cef_base_widget.cc 
  src/cef/cef_base_widget.h 
  src/cef/cef_handler.cc 
  src/cef/cef_handler.h 
  src/cef/cef_widget.cc 
  src/cef/cef_widget.h 
  src/cef/cef_base_widget_linux.cc 
  src/cef/cef_embed_window_linux.cc 
  src/cef/cef_embed_window_linux.h 
  src/cef/cef_linux.cc
  src/doogie.qrc
)

# Target executable names.
set(CEF_TARGET ${PROJECT_NAME})

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

message(STATUS "CEF_LIB_DEBUG=${CEF_LIB_DEBUG}")
message(STATUS "CEF_LIB_RELEASE=${CEF_LIB_RELEASE}")
message(STATUS "CEF_TARGET_OUT_DIR=${CEF_TARGET_OUT_DIR}")
message(STATUS "CEF_LIBCEF_DLL_WRAPPER_PATH=${CEF_LIBCEF_DLL_WRAPPER_PATH}")
message(STATUS "CEF_RESOURCE_DIR=${CEF_RESOURCE_DIR}")

if(OS_LINUX)
  #SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})

  # add_dependencies(${CEF_TARGET} libcef_dll_wrapper)

  # Set rpath so that libraries can be placed next to the executable.
  set_target_properties(${CEF_TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN")
  set_target_properties(${CEF_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
  set_target_properties(${CEF_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})

  # Copy binary and resource files to the target output directory.
  COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
  COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
  if (EXISTS "${CEF_BINARY_DIR}/libminigbm.so")
    COPY_FILES("${CEF_TARGET}" "libminigbm.so" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
  endif()

  # Set SUID permissions on the chrome-sandbox target.
  SET_LINUX_SUID_PERMISSIONS("${CEF_TARGET}" "${CEF_TARGET_OUT_DIR}/chrome-sandbox")
endif()

link_directories(${CEF_BINARY_DIR} ${CEF_LIBCEF_DLL_WRAPPER_PATH})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES} ${QT_LIBRARIES}  libcef_lib ${CEF_LIBCEF_DLL_WRAPPER_PATH}/libcef_dll_wrapper.a ${CEF_STANDARD_LIBS}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_chart3d.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
