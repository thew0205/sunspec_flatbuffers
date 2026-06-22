
set(TEST_NAME sunspec_set_value_writer_test)

set(TEST_MAIN_SRC 
                test_main.cpp
                )

add_executable(${TEST_NAME}
        ${TEST_MAIN_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        pico_stdlib
        generic_lib
        modbus_slave_lib
        sunspec
        sunspec_set_value_common_writer_test
)

target_compile_definitions(${TEST_NAME} PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES=1
)

pico_enable_stdio_usb(${TEST_NAME} 1)
pico_enable_stdio_uart(${TEST_NAME} 1)
pico_add_extra_outputs(${TEST_NAME})

target_include_directories(${TEST_NAME} PRIVATE
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")









