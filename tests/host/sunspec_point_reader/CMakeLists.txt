
set(TEST_NAME sunspec_point_reader_test)

set(TEST_MAIN_SRC 
                test_main.cpp
                )

add_executable(${TEST_NAME}
        ${TEST_MAIN_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        generic_lib
        modbus_slave_lib
        sunspec
        sunspec_point_common_reader_test
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")





