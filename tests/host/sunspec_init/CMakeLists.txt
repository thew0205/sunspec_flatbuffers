
set(TEST_NAME sunspec_init_test)

set(SUNSPEC_TEST_SRC 
                        test_main.cpp
                        sunspec_init_test.cpp
                        ModbusADU.cpp
                        ModbusRTUComm.cpp
                        ModbusRTUSlave.cpp
                        ModbusSlaveLogic.cpp
                        )

add_executable(${TEST_NAME}
        ${TEST_MAIN_SRC}
        ${SUNSPEC_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        generic_lib
        modbusmaster_lib
        sunspec
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")





