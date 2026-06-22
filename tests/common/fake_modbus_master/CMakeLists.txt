
set(TEST_NAME fake_modbus_master)

set(SUNSPEC_TEST_SRC
        fake_modbus_master.cpp
)

add_library(${TEST_NAME}
        ${SUNSPEC_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        # CppUTest
        # CppUTestExt
        # generic_lib
        modbus_master_lib
)

target_compile_definitions(${TEST_NAME} PUBLIC)

target_include_directories(${TEST_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)





