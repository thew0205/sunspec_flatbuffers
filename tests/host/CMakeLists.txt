# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

project(sunspec_host_test C CXX ASM)
set(TESTS OFF CACHE BOOL "Disable tests" FORCE)

add_compile_definitions(VIRTUAL_TEST=virtual)

# include(FetchContent)

# FetchContent_Declare(
#     CppUTest
#     GIT_REPOSITORY https://github.com/cpputest/cpputest.git
#     GIT_TAG v4.0
# )

# FetchContent_MakeAvailable(CppUTest)

add_subdirectory(${SUNSPEC_ROOT_DIR}/tests/third_party/cpputest ${CMAKE_BINARY_DIR}/third_party/cpputest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(${SUNSPEC_ROOT_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(third_party/generic)
add_subdirectory(third_party/modbus_master)
add_subdirectory(third_party/modbus_slave)

add_subdirectory(${SUNSPEC_ROOT_DIR}/tests/common ${CMAKE_BINARY_DIR}/common)

add_subdirectory(flatbuffer)
add_subdirectory(sunspec_init_writer)
add_subdirectory(sunspec_set_value_writer)

# add_subdirectory(sunspec_point_reader)
# add_subdirectory(sunspec_group_reader)
# add_subdirectory(sunspec_model_reader)
# add_subdirectory(sunspec_device_reader)

