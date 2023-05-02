cmake_minimum_required(VERSION 3.5)
project(lab_08 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -m80387 -masm=intel -Wall -Werror -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m80387 -mno-80387  -masm=intel -Wall -Werror")
add_executable(lab_08 main.cpp test_functions.h)

install(TARGETS lab_08
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
