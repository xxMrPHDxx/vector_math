#ifndef MAT3_HPP
#define MAT3_HPP

#include <ostream>

#ifdef minor
#undef minor
#endif

class mat3 {
public:
    float data[9];
    mat3();
    mat3(
        float, float, float,
        float, float, float,
        float, float, float
    );
    mat3(const mat3&);
    float determinant();
    float& operator [](int idx){ return this->data[idx]; }
    friend std::ostream& operator <<(std::ostream&, const mat3&);
    static mat3 identity();
    static mat3 invert(mat3&);
    static mat3 transpose(const mat3&);
private:
    static mat3 minor(const mat3&);
};

#endif