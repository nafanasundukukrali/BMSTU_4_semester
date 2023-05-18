cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(lab_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "-fconcepts-diagnostics-depth=3 -g3")
find_package(Qt6 REQUIRED COMPONENTS Test)

set(FILES matrix.h
    matrix.hpp
    iterator.h
    iterator.hpp
    matrixbase.h
#    matrixrow.h
#    matrixrow.hpp
    const_iterator.h
    const_iterator.hpp
    exceptionmatrix.h
    concepts.h
#    range.h
#    range.cpp
)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UP)
if (${CMAKE_BUILD_TYPE_UP} STREQUAL "RELEASE")
    add_executable(lab_02
        testmatrix.h
        testmatrix.cpp
        ${FILES})
else()
    SET(CMAKE_BUILD_TYPE Debug)
    add_executable(lab_02
        main.cpp
        ${FILES})
endif()

target_link_libraries(lab_02 PRIVATE Qt6::Test)

install(TARGETS lab_02
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


