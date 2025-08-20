cmake_minimum_required(VERSION 3.13)


project(sunspec_test C CXX ASM)


set(TESTS OFF CACHE BOOL "Disable tests" FORCE)

include(ExternalProject)

if(HOST_TEST)
    ExternalProject_Add(host_build
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/host
        BINARY_DIR ${CMAKE_BINARY_DIR}/host
        CMAKE_ARGS -DSUNSPEC_ROOT_DIR=${SUNSPEC_ROOT_DIR}
        INSTALL_COMMAND ""
    )
elseif(TARGET_TEST)
    ExternalProject_Add(pico_build
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/target
        BINARY_DIR ${CMAKE_BINARY_DIR}/target
        CMAKE_ARGS -DSUNSPEC_ROOT_DIR=${SUNSPEC_ROOT_DIR}
        INSTALL_COMMAND ""
    )
endif(HOST_TEST)
