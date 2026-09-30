cmake_minimum_required(VERSION 3.13)

# -fstack-usage emits a .su file per translation unit with each function's
# own stack-frame size -- analyze_backends.py parses these for the
# stack-usage-per-call metric (same technique as research_experiment/power_meter).
add_compile_options(-fstack-usage)

# set(BACKEND "c_define" CACHE STRING "SunSpec model-definition backend to build: c_define|json|flatbuffers")

if(BACKEND STREQUAL "flatbuffers")
        set(SUNSPEC_FLATBUFFERS_IMPLEMENTATION 1)
        set(SUNSPEC_JSON_IMPLEMENTATION 0)
elseif(BACKEND STREQUAL "json")
        set(SUNSPEC_FLATBUFFERS_IMPLEMENTATION 0)
        set(SUNSPEC_JSON_IMPLEMENTATION 1)
elseif(BACKEND STREQUAL "c_define")
        set(SUNSPEC_FLATBUFFERS_IMPLEMENTATION 0)
        set(SUNSPEC_JSON_IMPLEMENTATION 0)
else()
        message(FATAL_ERROR "Unknown BACKEND '${BACKEND}' -- expected c_define, json, or flatbuffers")
endif()

add_subdirectory(${SUNSPEC_ROOT_DIR}/src ${CMAKE_BINARY_DIR}/src)

# get_filename_component(SUNSPEC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)

# Four variants, sharing one timed-loop/heap-profiling entry point
# (harness_main.cpp) and differing only in what walk() does per call --
# same "separate translation units, shared main" pattern as
# research_experiment/power_meter's deserialization harness. noop is a true
# baseline (touches nothing from the sunspec library, so none of
# libsunspec.a gets linked in) that analyze_backends.py nets the others
# against for timing.
add_library(experiment_noop_lib
                noop.cpp
        )
foreach(variant load_only walk_shallow walk_deep)
        add_library(experiment_${variant}_lib
                ${variant}.cpp
        )
        target_link_libraries(experiment_${variant}_lib PUBLIC sunspec)
endforeach()
