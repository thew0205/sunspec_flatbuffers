cmake_minimum_required(VERSION 3.13)

project(sunspec C CXX ASM)

if(NOT DEFINED SUNSPEC_ROOT_DIR OR SUNSPEC_ROOT_DIR STREQUAL "" OR NOT EXISTS "${SUNSPEC_ROOT_DIR}/src")
        message(FATAL_ERROR "SUNSPEC_ROOT_DIR must be defined and must point to the root of the project where src folder and the include folders are located")
endif()
set(SUNSPEC_FLATBUFFERS_IMPLEMENTATION 1)
set(SUNSPEC_NAKEDBYTES_IMPLEMENTATION 2)
set(SUNSPEC_PROTOBUF_IMPLEMENTATION 3)
set(SUNSPEC_NANOPB_IMPLEMENTATION 4)
set(SUNSPEC_ADAPTER_IMPLEMENTATION ${SUNSPEC_FLATBUFFERS_IMPLEMENTATION} CACHE STRING "The Sunspec adapter implementation to use (FLATBUFFER or NAKEDBYTES)" FORCE)

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

if(${SUNSPEC_ADAPTER_IMPLEMENTATION} STREQUAL SUNSPEC_FLATBUFFERS_IMPLEMENTATION)
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
elseif(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL SUNSPEC_NAKEDBYTES_IMPLEMENTATION)
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
elseif(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL SUNSPEC_PROTOBUF_IMPLEMENTATION OR SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL SUNSPEC_NANOPB_IMPLEMENTATION)
        set(MODEL_FILES
                models/protobuf/protobuf_array_model_1.cpp
                models/protobuf/protobuf_array_model_101.cpp
                models/protobuf/protobuf_array_model_101.cpp
                models/protobuf/protobuf_array_model_112.cpp
                models/protobuf/protobuf_array_model_113.cpp
                models/protobuf/protobuf_array_model_120.cpp
                models/protobuf/protobuf_array_model_126.cpp
                models/protobuf/protobuf_array_model_160.cpp
        )
        if(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL SUNSPEC_PROTOBUF_IMPLEMENTATION)
                find_package(Protobuf CONFIG QUIET)
                set(SUNSPEC_LINK_LIBRARY protobuf::libprotobuf ${SUNSPEC_LINK_LIBRARY})

                set(MODEL_FILES
                        ${MODEL_FILES}
                        ${SUNSPEC_ROOT_DIR}/include/adapters/protobuf/sunspec_model_definition.pb.cc
                )
        elseif(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL SUNSPEC_NANOPB_IMPLEMENTATION)
                add_library(nanopb STATIC
                        ${SUNSPEC_ROOT_DIR}/third_party/nanopb/pb_decode.c
                        ${SUNSPEC_ROOT_DIR}/third_party/nanopb/pb_encode.c
                        ${SUNSPEC_ROOT_DIR}/third_party/nanopb/pb_common.c
                )
                target_include_directories(nanopb PUBLIC ${SUNSPEC_ROOT_DIR}/third_party/nanopb/)
                set(SUNSPEC_LINK_LIBRARY nanopb ${SUNSPEC_LINK_LIBRARY})

                set(MODEL_FILES
                        ${MODEL_FILES}
                        ${SUNSPEC_ROOT_DIR}/include/adapters/nanopb/sunspec_model_definition.pb.c
                )
        endif(SUNSPEC_ADAPTER_IMPLEMENTATION STREQUAL SUNSPEC_PROTOBUF_IMPLEMENTATION)

else()
        message(FATAL_ERROR "SUNSPEC_ADAPTER_IMPLEMENTATION has an invalid value: ${SUNSPEC_ADAPTER_IMPLEMENTATION}. Valid values are FLATBUFFER and NAKEDBYTES.")
endif(${SUNSPEC_ADAPTER_IMPLEMENTATION} STREQUAL SUNSPEC_FLATBUFFERS_IMPLEMENTATION)

add_library(${PROJECT_NAME}
        ${SUNSPEC_FILES}
        ${SUNSPEC_FILES_READER}
        ${SUNSPEC_FILES_WRITER}
        ${MODEL_FILES}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
        SUNSPEC_ADAPTER_IMPLEMENTATION=${SUNSPEC_ADAPTER_IMPLEMENTATION}
        SUNSPEC_FLATBUFFERS_IMPLEMENTATION=${SUNSPEC_FLATBUFFERS_IMPLEMENTATION}
        SUNSPEC_NAKEDBYTES_IMPLEMENTATION=${SUNSPEC_NAKEDBYTES_IMPLEMENTATION}
        SUNSPEC_PROTOBUF_IMPLEMENTATION=${SUNSPEC_PROTOBUF_IMPLEMENTATION}
)
# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUNSPEC_LINK_LIBRARY})

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PUBLIC
        ${SUNSPEC_ROOT_DIR}/
        ${SUNSPEC_ROOT_DIR}/include/adapters/flatbuffers
        ${SUNSPEC_ROOT_DIR}/include
        ${SUNSPEC_ROOT_DIR}/third_party/modbus_slave/include
        ${SUNSPEC_ROOT_DIR}/third_party/modbus_master/include
)



