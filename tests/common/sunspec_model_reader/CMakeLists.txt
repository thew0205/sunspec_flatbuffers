
set(TEST_NAME sunspec_model_common_reader_test)

set(SUNSPEC_TEST_SRC 
                        sunspec_model_reader_test.cpp
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
        fake_modbus_master
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)





