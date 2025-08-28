
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TESTS OFF CACHE BOOL "Disable tests" FORCE)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(sunspec_pai_target_test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()
set(TESTS OFF CACHE BOOL "Disable tests" FORCE)

include(FetchContent)

FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG v4.0
)

FetchContent_MakeAvailable(CppUTest)

set(TESTS OFF CACHE BOOL "Disable tests" FORCE)

# add_subdirectory(${SUNSPEC_ROOT_DIR}/tests/third_party/cpputest ${CMAKE_BINARY_DIR}/third_party/cpputest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${SUNSPEC_ROOT_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(generic)
add_subdirectory(modbus)
add_subdirectory(pzem_temp)

add_subdirectory(flatbuffer)
add_subdirectory(sunspec_init)
add_subdirectory(sunspec_set_value)
