cmake_minimum_required(VERSION 3.5)

project(lab_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_02 main.cpp matrix.h matrix.cpp iterator.h iterator.cpp)

install(TARGETS lab_02
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
