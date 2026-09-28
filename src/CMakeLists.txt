cmake_minimum_required(VERSION 3.13)

project(sunspec C CXX ASM)

if(NOT DEFINED SUNSPEC_ROOT_DIR OR SUNSPEC_ROOT_DIR STREQUAL "" OR NOT EXISTS "${SUNSPEC_ROOT_DIR}/src")
        message(FATAL_ERROR "SUNSPEC_ROOT_DIR must be defined and must point to the root of the project where src folder and the include folders are located")
endif()

set(USER_FLATBUFFERS_IMPLEMENTATION 1)


add_library(${PROJECT_NAME})

set(SUNSPEC_FILES
        sunspec.cpp
        model_definitions.cpp
)

if(NOT USER_FLATBUFFERS_IMPLEMENTATION)
        list(APPEND SUNSPEC_FILES
                model_definition.cpp
        )
endif()


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

if(USER_FLATBUFFERS_IMPLEMENTATION)
set(MODEL_FILES
        models/flatbuffer_array_model_1.cpp
        models/flatbuffer_array_model_2.cpp
        models/flatbuffer_array_model_3.cpp
        models/flatbuffer_array_model_4.cpp
        models/flatbuffer_array_model_5.cpp
        models/flatbuffer_array_model_6.cpp
        models/flatbuffer_array_model_7.cpp
        models/flatbuffer_array_model_8.cpp
        models/flatbuffer_array_model_9.cpp
        models/flatbuffer_array_model_10.cpp
        models/flatbuffer_array_model_11.cpp
        models/flatbuffer_array_model_12.cpp
        models/flatbuffer_array_model_13.cpp
        models/flatbuffer_array_model_14.cpp
        models/flatbuffer_array_model_15.cpp
        models/flatbuffer_array_model_16.cpp
        models/flatbuffer_array_model_17.cpp
        models/flatbuffer_array_model_18.cpp
        models/flatbuffer_array_model_19.cpp
        models/flatbuffer_array_model_101.cpp
        models/flatbuffer_array_model_102.cpp
        models/flatbuffer_array_model_103.cpp
        models/flatbuffer_array_model_111.cpp
        models/flatbuffer_array_model_112.cpp
        models/flatbuffer_array_model_113.cpp
        models/flatbuffer_array_model_120.cpp
        models/flatbuffer_array_model_121.cpp
        models/flatbuffer_array_model_122.cpp
        models/flatbuffer_array_model_123.cpp
        models/flatbuffer_array_model_124.cpp
        models/flatbuffer_array_model_125.cpp
        models/flatbuffer_array_model_126.cpp
        models/flatbuffer_array_model_127.cpp
        models/flatbuffer_array_model_128.cpp
        models/flatbuffer_array_model_129.cpp
        models/flatbuffer_array_model_130.cpp
        models/flatbuffer_array_model_131.cpp
        models/flatbuffer_array_model_132.cpp
        models/flatbuffer_array_model_133.cpp
        models/flatbuffer_array_model_134.cpp
        models/flatbuffer_array_model_135.cpp
        models/flatbuffer_array_model_136.cpp
        models/flatbuffer_array_model_137.cpp
        models/flatbuffer_array_model_138.cpp
        models/flatbuffer_array_model_139.cpp
        models/flatbuffer_array_model_140.cpp
        models/flatbuffer_array_model_141.cpp
        models/flatbuffer_array_model_142.cpp
        models/flatbuffer_array_model_143.cpp
        models/flatbuffer_array_model_144.cpp
        models/flatbuffer_array_model_145.cpp
        models/flatbuffer_array_model_160.cpp
        models/flatbuffer_array_model_201.cpp
        models/flatbuffer_array_model_202.cpp
        models/flatbuffer_array_model_203.cpp
        models/flatbuffer_array_model_204.cpp
        models/flatbuffer_array_model_211.cpp
        models/flatbuffer_array_model_212.cpp
        models/flatbuffer_array_model_213.cpp
        models/flatbuffer_array_model_214.cpp
        models/flatbuffer_array_model_220.cpp
        models/flatbuffer_array_model_302.cpp
        models/flatbuffer_array_model_303.cpp
        models/flatbuffer_array_model_304.cpp
        models/flatbuffer_array_model_305.cpp
        models/flatbuffer_array_model_306.cpp
        models/flatbuffer_array_model_307.cpp
        models/flatbuffer_array_model_308.cpp
        models/flatbuffer_array_model_401.cpp
        models/flatbuffer_array_model_402.cpp
        models/flatbuffer_array_model_403.cpp
        models/flatbuffer_array_model_404.cpp
        models/flatbuffer_array_model_501.cpp
        models/flatbuffer_array_model_502.cpp
        models/flatbuffer_array_model_601.cpp
        models/flatbuffer_array_model_701.cpp
        models/flatbuffer_array_model_702.cpp
        models/flatbuffer_array_model_703.cpp
        models/flatbuffer_array_model_704.cpp
        models/flatbuffer_array_model_705.cpp
        models/flatbuffer_array_model_706.cpp
        models/flatbuffer_array_model_707.cpp
        models/flatbuffer_array_model_708.cpp
        models/flatbuffer_array_model_709.cpp
        models/flatbuffer_array_model_710.cpp
        models/flatbuffer_array_model_711.cpp
        models/flatbuffer_array_model_712.cpp
        models/flatbuffer_array_model_713.cpp
        models/flatbuffer_array_model_714.cpp
        models/flatbuffer_array_model_715.cpp
        models/flatbuffer_array_model_801.cpp
        models/flatbuffer_array_model_802.cpp
        models/flatbuffer_array_model_803.cpp
        models/flatbuffer_array_model_804.cpp
        models/flatbuffer_array_model_805.cpp
        models/flatbuffer_array_model_806.cpp
        models/flatbuffer_array_model_807.cpp
        models/flatbuffer_array_model_808.cpp
        models/flatbuffer_array_model_809.cpp
        models/flatbuffer_array_model_63001.cpp
        models/flatbuffer_array_model_63002.cpp
        models/flatbuffer_array_model_64001.cpp
        models/flatbuffer_array_model_64020.cpp
        models/flatbuffer_array_model_64101.cpp
        models/flatbuffer_array_model_64111.cpp
        models/flatbuffer_array_model_64112.cpp
        models/flatbuffer_array_model_64410.cpp
        models/flatbuffer_array_model_64411.cpp
        models/flatbuffer_array_model_64412.cpp
        models/flatbuffer_array_model_64413.cpp
        models/flatbuffer_array_model_64414.cpp
        models/flatbuffer_array_model_64415.cpp
)
target_compile_definitions(${PROJECT_NAME} PUBLIC SUNSPEC_FLATBUFFERS_IMPLEMENTATION=1)

else()
set(MODEL_FILES
        models/model1.cpp
        models/model2.cpp
        models/model3.cpp
        models/model4.cpp
        models/model5.cpp
        models/model6.cpp
        models/model7.cpp
        models/model8.cpp
        models/model9.cpp
        models/model10.cpp
        models/model11.cpp
        models/model12.cpp
        models/model13.cpp
        models/model14.cpp
        models/model15.cpp
        models/model16.cpp
        models/model17.cpp
        models/model18.cpp
        models/model19.cpp
        models/model101.cpp
        models/model102.cpp
        models/model103.cpp
        models/model111.cpp
        models/model112.cpp
        models/model113.cpp
        models/model120.cpp
        models/model121.cpp
        models/model122.cpp
        models/model123.cpp
        models/model124.cpp
        models/model125.cpp
        models/model126.cpp
        models/model127.cpp
        models/model128.cpp
        models/model129.cpp
        models/model130.cpp
        models/model131.cpp
        models/model132.cpp
        models/model133.cpp
        models/model134.cpp
        models/model135.cpp
        models/model136.cpp
        models/model137.cpp
        models/model138.cpp
        models/model139.cpp
        models/model140.cpp
        models/model141.cpp
        models/model142.cpp
        models/model143.cpp
        models/model144.cpp
        models/model145.cpp
        models/model160.cpp
        models/model201.cpp
        models/model202.cpp
        models/model203.cpp
        models/model204.cpp
        models/model211.cpp
        models/model212.cpp
        models/model213.cpp
        models/model214.cpp
        models/model220.cpp
        models/model302.cpp
        models/model303.cpp
        models/model304.cpp
        models/model305.cpp
        models/model306.cpp
        models/model307.cpp
        models/model308.cpp
        models/model401.cpp
        models/model402.cpp
        models/model403.cpp
        models/model404.cpp
        models/model501.cpp
        models/model502.cpp
        models/model601.cpp
        models/model701.cpp
        models/model702.cpp
        models/model703.cpp
        models/model704.cpp
        models/model705.cpp
        models/model706.cpp
        models/model707.cpp
        models/model708.cpp
        models/model709.cpp
        models/model710.cpp
        models/model711.cpp
        models/model712.cpp
        models/model713.cpp
        models/model714.cpp
        models/model715.cpp
        models/model801.cpp
        models/model802.cpp
        models/model803.cpp
        models/model804.cpp
        models/model805.cpp
        models/model806.cpp
        models/model807.cpp
        models/model808.cpp
        models/model809.cpp
        models/model63001.cpp
        models/model63002.cpp
        models/model64001.cpp
        models/model64020.cpp
        models/model64101.cpp
        models/model64111.cpp
        models/model64112.cpp
        models/model64410.cpp
        models/model64411.cpp
        models/model64412.cpp
        models/model64413.cpp
        models/model64414.cpp
        models/model64415.cpp
)
endif()

target_sources(${PROJECT_NAME} PRIVATE
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



