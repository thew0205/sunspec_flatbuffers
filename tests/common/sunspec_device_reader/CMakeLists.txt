
set(TEST_NAME sunspec_device_common_reader_test)

set(SUNSPEC_TEST_SRC 
                        sunspec_device_reader_test.cpp
                        )

add_library(${TEST_NAME}
        ${SUNSPEC_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        generic_lib
        modbus_master_lib
        sunspec
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)





