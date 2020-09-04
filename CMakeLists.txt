cmake_minimum_required( VERSION 3.0 )
project(vector_math)

set( SRCS
    src/mat3.cpp
    src/mat4.cpp
    src/vec3.cpp
    src/vec4.cpp
)

add_library( vector_math STATIC ${SRCS} )

add_subdirectory( tests )

install(
    DIRECTORY src/ 
    LIBRARY
    DESTINATION include/vector_math
    FILES_MATCHING PATTERN "*.hpp"
)
install(TARGETS vector_math DESTINATION lib)

include( CTest )
add_test( mat3 tests/mat3_test )
add_test( mat4 tests/mat4_test )
add_test( vec3 tests/vec3_test )