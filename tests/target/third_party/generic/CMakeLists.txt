project(generic_lib C CXX ASM)


set(generic
        src/HardwareSerial.cpp
        src/Print.cpp
        src/HardwareSerial.cpp 
        )

add_library(${PROJECT_NAME}
        ${generic}
)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} PRIVATE
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${SUNSPEC_ROOT_DIR}/third_party/generic/include
)


