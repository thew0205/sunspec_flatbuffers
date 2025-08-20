
set(TEST_NAME flatbuffer_test)

set(FLATBUFFER_TEST_SRC 
                        flatbuffer_test_utils.cpp
                        model_1_test.cpp
                        model_160_test.cpp
                        )

add_executable(${TEST_NAME}
        ${TEST_MAIN_SRC}
        ${FLATBUFFER_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        pico_stdlib
        sunspec
)

target_compile_definitions(${TEST_NAME} PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

target_include_directories(${TEST_NAME} PRIVATE
)

pico_add_extra_outputs(${TEST_NAME})
# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${TEST_NAME} 1)
pico_enable_stdio_usb(${TEST_NAME} 1)

target_compile_definitions(${TEST_NAME} PRIVATE
        PICO_DEFAULT_UART=0
        PICO_DEFAULT_UART_TX_PIN=16
        PICO_DEFAULT_UART_RX_PIN=17
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")





