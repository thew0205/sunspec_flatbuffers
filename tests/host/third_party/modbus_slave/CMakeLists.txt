project(modbus_slave_lib C CXX ASM)


set( MODBUS_SLAVE_SRC_FILES 
                        src/ModbusADU.cpp
                        src/ModbusRTUComm.cpp
                        src/ModbusRTUSlave.cpp
                        src/ModbusSlaveLogic.cpp
                        )



add_library(${PROJECT_NAME}  
                    ${MODBUS_SLAVE_SRC_FILES}
                    )


# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${SUNSPEC_ROOT_DIR}/third_party/modbus_slave/include
        ${SUNSPEC_ROOT_DIR}/third_party/generic/include
)



