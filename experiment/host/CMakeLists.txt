cmake_minimum_required(VERSION 3.13)

# Host (native, non-Pico) benchmark harness comparing the three SunSpec
# model-definition backends (c_define / json / flatbuffers) selected by
# src/CMakeLists.txt's SUNSPEC_FLATBUFFERS_IMPLEMENTATION /
# SUNSPEC_JSON_IMPLEMENTATION switches. Only one backend can be linked per
# configure (it's a library-wide compile-time choice), so analyze_backends.py
# drives three separate configure+build cycles, one per BACKEND value, each
# into its own build directory.

project(sunspec_model_definition_experiment_host C CXX)

# -fstack-usage emits a .su file per translation unit with each function's
# own stack-frame size -- analyze_backends.py parses these for the
# stack-usage-per-call metric (same technique as research_experiment/power_meter).
add_compile_options(-fstack-usage)

add_subdirectory(${SUNSPEC_ROOT_DIR}/experiment/common ${CMAKE_BINARY_DIR}/common)

foreach(variant noop load_only walk_shallow walk_deep)
        add_executable(experiment_${variant}
                harness_main.cpp
        )
        target_link_libraries(experiment_${variant} PRIVATE sunspec experiment_${variant}_lib)
endforeach()