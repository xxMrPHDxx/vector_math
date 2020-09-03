#ifndef MAT4_HPP
#define MAT4_HPP

#include <ostream>

class vec3;
class mat3;

class mat4 {
public:
    mat4();
    mat4(
        float,float,float,float,
        float,float,float,float,
        float,float,float,float,
        float,float,float,float
    );
    mat4(const mat4& o);
    float determinant();
    float& operator [](const int idx){ return this->data[idx]; }
    friend std::ostream& operator <<(std::ostream&, const mat4&);
    static mat4 identity();
    static mat4 invert(mat4&);
    static mat4 lookAt(vec3 eye, vec3 center, vec3 up);
    static mat4 transpose(const mat4&);
private:
    float data[16];
    static mat4 minor(const mat4&);
    static float minor(const mat4&, int, int);
};

#endif