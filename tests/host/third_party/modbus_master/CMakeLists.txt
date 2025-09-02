project(modbus_master_lib C CXX ASM)


set(MODBUS_MASTER_SRC_FILES src/modbus_master.cpp)



add_library(${PROJECT_NAME}  
                    ${MODBUS_MASTER_SRC_FILES}
                    )


# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
         ${SUNSPEC_ROOT_DIR}/third_party/modbus_master/include
        ${SUNSPEC_ROOT_DIR}/third_party/generic/include
)