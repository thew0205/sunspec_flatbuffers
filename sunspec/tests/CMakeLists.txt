cmake_minimum_required(VERSION 3.13)



include(FetchContent)

FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        v4.0
)

FetchContent_MakeAvailable(CppUTest)

if(TARGET_TEST)
    set(TESTS OFF CACHE BOOL "Disable tests" FORCE)
endif()

if(TARGET_TEST)
    add_subdirectory(target)
endif()
if(HOST_TEST)
    add_subdirectory(host)
endif()