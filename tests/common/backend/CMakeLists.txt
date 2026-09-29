
set(TEST_NAME backend_common_test)

set(BACKEND_TEST_SRC 
                        backend_test_utils.cpp
                        model_1_test.cpp
                        model_160_test.cpp
                        )

add_library(${TEST_NAME}
        ${BACKEND_TEST_SRC}
)

target_link_libraries(${TEST_NAME}
        CppUTest
        CppUTestExt
        sunspec
)

target_compile_definitions(${TEST_NAME} PRIVATE)

target_include_directories(${TEST_NAME} PRIVATE
)






