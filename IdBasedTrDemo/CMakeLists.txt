cmake_minimum_required(VERSION 3.14)

project(IdBasedTrDemo LANGUAGES CXX)

#QT dir
#set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/Qt5-msvc14/5.6/msvc2015_64" )

# Instruct CMake to run moc/resource/ui automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# QT5 modules
find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    utils/InternationalUtil.cpp
    utils/InternationalUtil.h
    widget.cpp
    widget.h
    widget.ui
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

# deploy
install(TARGETS ${PROJECT_NAME}
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)
install(TARGETS ${PROJECT_NAME}
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)
