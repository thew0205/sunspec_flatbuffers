project(generic_lib C CXX ASM)


FILE(GLOB generic src/*.cpp include/*.h)

add_library(${PROJECT_NAME}  
                    ${generic}
                    )


target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SUNSPEC_ROOT_DIR}/third_party/generic/include
)


