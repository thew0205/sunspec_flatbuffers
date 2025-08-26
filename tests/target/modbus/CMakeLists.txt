project(modbusmaster_lib C CXX ASM)


FILE(GLOB modbus src/*.cpp inc/*.h)



add_library(${PROJECT_NAME}  
                    ${modbus}
                    )



# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} PRIVATE
        pico_stdlib
        )

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${SUNSPEC_ROOT_DIR}/third_party/modbus/inc
        ${SUNSPEC_ROOT_DIR}/third_party/generic/include
)


