cmake_minimum_required(VERSION 3.5)

project(lab_08_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m80387 -mno-80387  -masm=intel -Wall -Werror")
add_executable(lab_08_2 main.cpp)

install(TARGETS lab_08_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
