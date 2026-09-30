cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)


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

project(sunspec_model_definition_experiment_host C CXX)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


add_compile_options(-fstack-usage)

add_subdirectory(${SUNSPEC_ROOT_DIR}/experiment/common ${CMAKE_BINARY_DIR}/common)

add_executable(experiment_noop harness_main_noop.cpp)
target_link_libraries(experiment_noop PRIVATE experiment_noop_lib pico_stdlib)
pico_enable_stdio_usb(experiment_noop 1)
pico_enable_stdio_uart(experiment_noop 1)
pico_add_extra_outputs(experiment_noop)

foreach(variant load_only walk_shallow walk_deep)
        add_executable(experiment_${variant}
                harness_main.cpp
        )
        target_link_libraries(experiment_${variant} PRIVATE experiment_${variant}_lib pico_stdlib)
        pico_enable_stdio_usb(experiment_${variant} 1)
        pico_enable_stdio_uart(experiment_${variant} 1)
        pico_add_extra_outputs(experiment_${variant})
endforeach()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")
