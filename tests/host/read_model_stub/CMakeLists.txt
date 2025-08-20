
set(TEST_NAME SunspecReadModelFake)

add_executable(${TEST_NAME} temp.cpp)

# Add the standard library to the build
target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        sunspec_src
        )

target_compile_definitions(${TEST_NAME} PRIVATE 
PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

# Add the standard include files to the build
target_include_directories(${TEST_NAME} PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
        # ${CMAKE_CURRENT_LIST_DIR}/modbus/inc     
)
