cmake_minimum_required(VERSION 3.5)

project(lab_03_code VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set(CMAKE_DEBUG_CXX_FLAGS "-fconcepts-diagnostics-depth=3 -g3")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        exceptions/exception.h
        objects/object.h
        objects/composite.h objects/composite.cpp
        objects/visibleobjects/visibleobject.h
        objects/invisibleobjects/invisibleobject.h objects/invisibleobjects/invisibleobject.cpp
        objects/invisibleobjects/camera/camera.h objects/invisibleobjects/camera/camera.cpp
        objects/visibleobjects/model/model.h objects/visibleobjects/model/model.cpp
        objects/visibleobjects/model/modeldata/modeldata.h objects/visibleobjects/model/modeldata/modeldata.cpp
        objects/visibleobjects/model/modeldata/point/point.h objects/visibleobjects/model/modeldata/point/point.cpp
        objects/visibleobjects/model/modeldata/edge/edge.h objects/visibleobjects/model/modeldata/edge/edge.cpp
        objects/visibleobjects/basemodel.h
    )
string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UP)
if (${CMAKE_BUILD_TYPE_UP} STREQUAL "RELEASE")
    set(PROJECT_SOURCES main.cpp ${PROJECT_SOURCES})
else()
    set(CMAKE_BUILD_TYPE Debug)
    set(PROJECT_SOURCES
        unittesting/testmodeldata.h unittesting/testmodeldata.cpp
        unittesting/testpoint.h unittesting/testpoint.cpp
        unittesting/testedge.h unittesting/testedge.cpp
        unittesting/unittesting.cpp
        ${PROJECT_SOURCES})
#    add_executable(lab_03_code
#        unittesting/unittesting.cpp
#        ${FILES})
endif()

include_directories(
    objects/
    objects/invisibleobjects/
    objects/visibleobjects/
    objects/visibleobjects/model/
    objects/visibleobjects/model/modeldata/
    objects/visibleobjects/model/modeldata/point
    objects/visibleobjects/model/modeldata/edge
    exceptions/
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab_03_code
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lab_03_code APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(lab_03_code SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(lab_03_code
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(lab_03_code PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

set_target_properties(lab_03_code PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS lab_03_code
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_03_code)
endif()
