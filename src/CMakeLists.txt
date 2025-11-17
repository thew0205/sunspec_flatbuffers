cmake_minimum_required(VERSION 3.13)

project(sunspec C CXX ASM)

if(NOT DEFINED SUNSPEC_ROOT_DIR OR SUNSPEC_ROOT_DIR STREQUAL "" OR NOT EXISTS "${SUNSPEC_ROOT_DIR}/src")
        message(FATAL_ERROR "SUNSPEC_ROOT_DIR must be defined and must point to the root of the project where src folder and the include folders are located")
endif()
set(SUNSPEC_ADAPTER_IMPLEMENTATION FLATBUFFER CACHE STRING "The Sunspec adapter implementation to use (FLATBUFFER or NAKEDBYTES)" FORCE)

set(SUNSPEC_FILES
        sunspec.cpp
        model_definitions.cpp
)

set(SUNSPEC_FILES_READER
        reader/sunspec_point_reader.cpp
        reader/sunspec_group_reader.cpp
        reader/sunspec_model_reader.cpp
        reader/sunspec_device_reader.cpp
)
set(SUNSPEC_FILES_WRITER
        writer/sunspec_point_writer.cpp
        writer/sunspec_group_writer.cpp
        writer/sunspec_model_writer.cpp
        writer/sunspec_device_writer.cpp
)

if(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL "FLATBUFFER")
set(MODEL_FILES
        models/flatbuffers/flatbuffers_array_model_1.cpp
        models/flatbuffers/flatbuffers_array_model_101.cpp
        models/flatbuffers/flatbuffers_array_model_101.cpp
        models/flatbuffers/flatbuffers_array_model_112.cpp
        models/flatbuffers/flatbuffers_array_model_113.cpp
        models/flatbuffers/flatbuffers_array_model_120.cpp
        models/flatbuffers/flatbuffers_array_model_126.cpp
        models/flatbuffers/flatbuffers_array_model_160.cpp
)
elseif(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL "NAKEDBYTES")
set(MODEL_FILES
        models/nakedbytes/nakedbytes_array_model_1.cpp
        models/nakedbytes/nakedbytes_array_model_101.cpp
        models/nakedbytes/nakedbytes_array_model_101.cpp
        models/nakedbytes/nakedbytes_array_model_112.cpp
        models/nakedbytes/nakedbytes_array_model_113.cpp
        models/nakedbytes/nakedbytes_array_model_120.cpp
        models/nakedbytes/nakedbytes_array_model_126.cpp
        models/nakedbytes/nakedbytes_array_model_160.cpp
)
else()
    message(FATAL_ERROR "SUNSPEC_ADAPTER_IMPLEMENTATION has an invalid value: ${SUNSPEC_ADAPTER_IMPLEMENTATION}. Valid values are FLATBUFFER and NAKEDBYTES.")
endif(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL "FLATBUFFER")

add_library(${PROJECT_NAME}
        ${SUNSPEC_FILES}
        ${SUNSPEC_FILES_READER}
        ${SUNSPEC_FILES_WRITER}
        ${MODEL_FILES}
)


# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} PRIVATE )

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${SUNSPEC_ROOT_DIR}/
        ${SUNSPEC_ROOT_DIR}/include
        ${SUNSPEC_ROOT_DIR}/third_party/modbus_slave/include
        ${SUNSPEC_ROOT_DIR}/third_party/modbus_master/include
)



