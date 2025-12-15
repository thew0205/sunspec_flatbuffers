# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

project(sunspec_common_test C CXX ASM)

# add_subdirectory(fake_modbus_master)
add_subdirectory(flatbuffers)
# add_subdirectory(sunspec_init_writer)
# add_subdirectory(sunspec_set_value_writer)

# add_subdirectory(sunspec_point_reader)
# add_subdirectory(sunspec_group_reader)
# add_subdirectory(sunspec_model_reader)
# add_subdirectory(sunspec_device_reader)
