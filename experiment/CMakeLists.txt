cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)


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
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(sunspec_pai_target_test C CXX ASM)
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()
set(TEST_NAME flatbuf)

set(FLATBUFFER_TEST_SRC 
                        # flatbuffer_test_utils.cpp
                        # model_1_test.cpp
                        # model_160_test.cpp
                test_main.cpp

                        )
set(SUNSPEC_ROOT_DIR "/home/busoye_tm/Documents/matthew/projects/sunspec_flatbuffer")
add_subdirectory(${SUNSPEC_ROOT_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_executable(${TEST_NAME}
        ${FLATBUFFER_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        sunspec
        pico_stdlib
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)

pico_enable_stdio_usb(${TEST_NAME} 1)
pico_enable_stdio_uart(${TEST_NAME} 1)
pico_add_extra_outputs(${TEST_NAME})


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")






# set(TEST_NAME sunspec_set_value_writer_test)

# set(TEST_MAIN_SRC 
#                 test_main.cpp
#                 )

# add_executable(${TEST_NAME}
#         ${TEST_MAIN_SRC}
# )

# target_link_libraries(${TEST_NAME}
#         CppUTest
#         CppUTestExt
#         generic_lib
#         modbus_slave_lib
#         sunspec
#         sunspec_set_value_common_writer_test
# )

# target_compile_definitions(${TEST_NAME} PRIVATE)

# target_include_directories(${TEST_NAME} PRIVATE
# )
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")





