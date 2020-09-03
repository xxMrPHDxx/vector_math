cmake_minimum_required( VERSION 3.0 )
project( tests )

include_directories( ../src )

add_executable( vec3_test src/vec3.cpp )
target_link_libraries( vec3_test vector_math )

add_executable( mat4_test src/mat4.cpp )
target_link_libraries( mat4_test vector_math )

add_executable( mat3_test src/mat3.cpp )
target_link_libraries( mat3_test vector_math )