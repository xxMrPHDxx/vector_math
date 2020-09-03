cmake_minimum_required( VERSION 3.0 )
project(vector_math)

set( SRCS
    src/mat4.cpp
    src/mat3.cpp
    src/vec3.cpp
)

add_library( vector_math STATIC ${SRCS} )

add_subdirectory( tests )