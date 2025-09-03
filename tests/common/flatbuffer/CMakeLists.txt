
set(TEST_NAME flatbuffer_common_test)

set(FLATBUFFER_TEST_SRC 
                        flatbuffer_test_utils.cpp
                        model_1_test.cpp
                        model_160_test.cpp
                        )

add_library(${TEST_NAME}
        ${FLATBUFFER_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        sunspec
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)






