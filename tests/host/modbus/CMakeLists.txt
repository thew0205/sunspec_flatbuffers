project(modbusmaster_lib C CXX ASM)


FILE(GLOB modbus src/*.cpp inc/*.h)



add_library(${PROJECT_NAME}  
                    ${modbus}
                    )


# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../generic/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../modbus/inc
        ${CMAKE_CURRENT_LIST_DIR}
)


