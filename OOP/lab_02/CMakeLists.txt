cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(lab_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-fconcepts-diagnostics-depth=2")
find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(lab_02
    matrix.h
    matrix.hpp
    iterator.h
    iterator.hpp
    matrixbase.h
    matrixbase.hpp
    matrixrow.h
    matrixrow.hpp
    testmatrixrow.h
    testmatrixrow.hpp
    const_iterator.h
    const_iterator.hpp
    exceptionmatrix.h
    exceptionmatrix.hpp
    main.cpp)
install(TARGETS lab_02
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
target_link_libraries(lab_02 PRIVATE Qt6::Test)


