
set(TEST_NAME sunspec_set_value_common_test)

set(SUNSPEC_TEST_SRC 
                sunspec_set_value_test.cpp
                        )

add_library(${TEST_NAME}
        ${SUNSPEC_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        generic_lib
        modbus_slave_lib
        sunspec
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)





