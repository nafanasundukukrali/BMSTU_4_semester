cmake_minimum_required(VERSION 3.5)

project(lab_09 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -masm=intel -g3")

add_executable(lab_09 main.cpp)

install(TARGETS lab_09
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
