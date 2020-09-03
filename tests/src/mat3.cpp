#include <iostream>
#include "mat3.hpp"

#define DEBUG(msg, ...) std::cout << msg << "\n"; __VA_ARGS__; std::cout << "=============================================\n"
#define LOG(obj) std::cout << obj << "\n"

int main(){
    // Default constructor
    mat3 m1;
    DEBUG("Default contructor: m1", LOG(m1));

    // Constructor with 9 floats
    mat3 m2(1,2,3,0,1,4,5,6,0);
    DEBUG("Constructor with 9 floats: m2", LOG(m2));

    // Copy constructor
    mat3 m3 = m2;
    DEBUG("Copy constructor: m3 = copy m2", LOG(m3));

    // Operator overloading []
    DEBUG(
        "Operator overloading []: m3[0] until m[3]", 
        LOG(m3[0]); LOG(m3[1]); LOG(m3[2]); LOG(m3[3])
    );

    // Determinant
    DEBUG("Determinant: m3", LOG(m3.determinant()));

    // Identity
    DEBUG("Identity: mat3::identity()", LOG(mat3::identity()));

    // Transpose
    DEBUG("Transpose: mat3::transpose(m3)", LOG(mat3::transpose(m3)));

    // Invert
    DEBUG("Invert: mat3::invert(m3)", LOG(mat3::invert(m3)));
}