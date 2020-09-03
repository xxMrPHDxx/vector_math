#include <iostream>
#include <iomanip>
#include <cmath>
#include "mat4.hpp"
#include "vec3.hpp"

#define DEBUG(msg, ...) std::cout << msg << "\n"; __VA_ARGS__; std::cout << "=============================================\n"
#define LOG(obj) std::cout << obj << "\n"

#define PI M_PI

int main(){
    // Default constructor
    mat4 m1;
    DEBUG("Default contructor: m1", LOG(m1));

    // Constructor with 16 floats
    mat4 m2(
        1, 0,-1,-1,
        0, 2, 0, 1,
        1,-1,-1, 2,
        2, 0,-1, 1
    );
    DEBUG("Constructor with 16 floats: m2", LOG(m2));

    // Copy constructor
    mat4 m3 = m2;
    DEBUG("Copy constructor: m3 = copy m2", LOG(m3));

    // Operator overloading []
    DEBUG(
        "Operator overloading []: m3[0] until m[3]", 
        LOG(m3[0]); LOG(m3[1]); LOG(m3[2]); LOG(m3[3])
    );

    // Determinant
    DEBUG("Determinant: m3", LOG(m3.determinant()));

    // Identity
    DEBUG("Identity: mat4::identity()", LOG(mat4::identity()));

    // Transpose
    DEBUG("Transpose: mat4::transpose(m3)", LOG(mat4::transpose(m3)));

    // Look at mat4
    mat4 m4 = mat4::lookAt(vec3(0,0,-8),vec3(0,0,0),vec3(0,1,0));
    DEBUG("Look at mat4: mat4::lookAt([0,0,-8],[0,0,0],[0,1,0])", LOG(m4));

    // Matrix multiply
    DEBUG("Matrix multiply: m3 * m3", LOG(m3 * m3));

    // Matrix translate
    DEBUG(
        "Matrix translate: mat4::identity().translate(1,2,3)", 
        LOG(mat4::identity().translate(1,2,3))
    );

    // Matrix rotateX
    DEBUG(
        "Matrix rotateX: mat4::identity().rotateX(PI)", 
        LOG(mat4::identity().rotateX(PI))
    );

    // Matrix rotateY
    DEBUG(
        "Matrix rotateY: mat4::identity().rotateY(PI)", 
        LOG(mat4::identity().rotateY(PI))
    );

    // Matrix rotateZ
    DEBUG(
        "Matrix rotateZ: mat4::identity().rotateZ(PI)", 
        LOG(mat4::identity().rotateZ(PI))
    );

    // Invert
    std::cout << std::fixed << std::setprecision(4);
    DEBUG("Invert: mat4::invert(m4)", LOG(mat4::invert(m4)));
}