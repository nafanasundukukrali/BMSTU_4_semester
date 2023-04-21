cmake_minimum_required(VERSION 3.5)

project(lab_07 LANGUAGES C ASM)

add_executable(lab_07 main.c string_functions.h string_functions.c strncpy.s)

install(TARGETS lab_07
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -m32")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -Wall -Werror -Wextra -m32")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
set(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -x assembler-with-cpp")
