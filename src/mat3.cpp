#include "mat3.hpp"

#define DET(a, b, c, d) (mat.data[a]*mat.data[d] - mat.data[b]*mat.data[c])
#define EPSILON 0.000001

mat3::mat3(){
    for(int i=0; i<9; i++) this->data[i] = 0.0f;
}

mat3::mat3(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22
){
    this->data[0] = m00; this->data[1] = m01; this->data[2] = m02;
    this->data[3] = m10; this->data[4] = m11; this->data[5] = m12;
    this->data[6] = m20; this->data[7] = m21; this->data[8] = m22;
}

mat3::mat3(const mat3& o){
    for(int i=0; i<9; i++) this->data[i] = o.data[i];
}

float mat3::determinant(){
    float a = this->data[0], b = this->data[1], c = this->data[2];
    float d = this->data[3], e = this->data[4], f = this->data[5];
    float g = this->data[6], h = this->data[7], i = this->data[8];
    return a*(e*i-f*h) - b*(d*i-f*g) + c*(d*h-e*g);
}

std::ostream& operator <<(std::ostream& out, const mat3& mat){
    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){
            out << ("%.4f", mat.data[r*3+c]);
            if(c < 2) out << " ";
        }
        if(r < 2) out << "\n";
    }
    return out;
}

mat3 mat3::identity(){
    return mat3(1,0,0,0,1,0,0,0,1);
}

mat3 mat3::invert(mat3& mat){
    float det = mat.determinant();
    if(std::abs(det) < EPSILON) return mat3::identity();
    det = 1.0f / det;
    mat3 M = mat3::minor(mat);
    for(int i=0; i<9; i++) M[i] *= i%2?-1:1 * det;
    return mat3::transpose(M);
}

mat3 mat3::minor(const mat3& mat){
    return mat3(
        DET(4,5,7,8), DET(3,5,6,8), DET(3,6,4,7),
        DET(1,2,7,8), DET(0,2,6,8), DET(0,6,1,7),
        DET(1,2,4,5), DET(0,2,3,5), DET(0,1,3,4)
    );
}

mat3 mat3::transpose(const mat3& mat){
    mat3 ret;
    for(int r=0; r<3; r++)
    for(int c=0; c<3; c++)
        ret[c*3+r] = mat.data[r*3+c];
    return ret;
}

#undef DET
#undef EPSILON