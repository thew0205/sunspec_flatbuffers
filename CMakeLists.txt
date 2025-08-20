# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SUNSPEC_ROOT_DIR ${CMAKE_SOURCE_DIR})

project(sunspec_lib C CXX ASM)


add_subdirectory(src)
if(SUNSPEC_TEST)
    add_subdirectory(tests)
endif(SUNSPEC_TEST)





