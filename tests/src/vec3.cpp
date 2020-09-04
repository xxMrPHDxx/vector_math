#include <iostream>

#include "test.hpp"
#include "vec3.hpp"

int main(){
    // Default constructor
    vec3 v1;
    DEBUG("Default constructor", LOG(v1));

    // Constructor with 3 floats
    vec3 v2(1,2,3);
    DEBUG("Constructor with 3 floats", LOG(v2));

    // Copy constructor
    vec3 v3 = v2;
    DEBUG("Copy constructor", LOG(v3));

    // Addition
    vec3 v4 = vec3::add(v2, v3);
    DEBUG("Addition", LOG(v4));

    // Cross
    vec3 v5 = vec3::cross(v2, v3);
    DEBUG("Cross", LOG(v5));

    // Dot
    float dot = vec3::dot(v2, v3);
    DEBUG("Dot", LOG(dot));

    // Magnitude
    float mag = vec3::mag(v2);
    DEBUG("Magnitude", LOG(mag));

    // Normalize
    vec3 norm = vec3::normalize(v2);
    DEBUG("Normalize", LOG(norm));
    ASSERT("Failed to normalize!", norm.x*norm.x+norm.y*norm.y+norm.z*norm.z <= 1);

    // Subtract
    vec3 sub = vec3::sub(v2, v3);
    DEBUG("Subtract", LOG(sub));

    ASSERT_EQUALS("sub.x should be 0", sub.x, 0);
    ASSERT_EQUALS("sub.y should be 0", sub.y, 0);
    ASSERT_EQUALS("sub.z should be 0", sub.z, 0);
}