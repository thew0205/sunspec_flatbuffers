# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(sunspec_lib C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

option(ON_TARGET_TEST "Set to ON if you want to build the tests for the target" ON)
option(HOST_TEST "Set to ON if you want to build the host tests" OFF)
if(ON_TARGET_TEST)
    set(TESTS OFF CACHE BOOL "Disable tests" FORCE)
endif()


add_subdirectory(sunspec)


set(TEST_NAME SunspecFlatBuffers)
add_subdirectory(generic)
add_executable(${TEST_NAME} sunspec_flatbuffer.cpp modbus.cpp ModbusADU.cpp ModbusRTUComm.cpp ModbusRTUSlave.cpp ModbusSlaveLogic.cpp)

target_link_libraries(${TEST_NAME}
        pico_stdlib
        generic_lib
        sunspec
        )



target_include_directories(${TEST_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
        ${CMAKE_CURRENT_LIST_DIR}/modbus/inc   
)

pico_add_extra_outputs(${TEST_NAME})
# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${TEST_NAME} 1)
pico_enable_stdio_usb(${TEST_NAME} 0)

target_compile_definitions(${TEST_NAME} PRIVATE
  PICO_DEFAULT_UART=0
  PICO_DEFAULT_UART_TX_PIN=16
  PICO_DEFAULT_UART_RX_PIN=17
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")





