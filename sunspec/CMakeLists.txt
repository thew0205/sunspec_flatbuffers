cmake_minimum_required(VERSION 3.13)

project(sunspec C CXX ASM)


set(SUNSPEC_FILES
                src/sunspec_utils.cpp
                )

set(SUNSPEC_FILES_READER 
                src/reader/sunspec_point_reader.cpp
                src/reader/sunspec_group_reader.cpp
                src/reader/sunspec_model_reader.cpp
                src/reader/sunspec_device_reader.cpp
                )
set(SUNSPEC_FILES_WRITER
                src/writer/sunspec_point_writer.cpp
                src/writer/sunspec_group_writer.cpp
                src/writer/sunspec_model_writer.cpp
                src/writer/sunspec_device_writer.cpp
                )
set(MODEL_FILES 
                src/models/flatbuffer_array_model_1.cpp
                src/models/flatbuffer_array_model_101.cpp
                src/models/flatbuffer_array_model_101.cpp
                src/models/flatbuffer_array_model_112.cpp
                src/models/flatbuffer_array_model_113.cpp
                src/models/flatbuffer_array_model_120.cpp
                src/models/flatbuffer_array_model_126.cpp
                src/models/flatbuffer_array_model_160.cpp
                )

add_library(${PROJECT_NAME}  
                    ${SUNSPEC_FILES}
                    ${SUNSPEC_FILES_READER}
                    ${SUNSPEC_FILES_WRITER}
                    ${MODEL_FILES}
                    )


# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} PRIVATE
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/modbus/inc    
        ${CMAKE_CURRENT_SOURCE_DIR}/modbus_writer    
)



add_subdirectory(tests)
