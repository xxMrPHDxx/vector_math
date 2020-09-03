#include "mat4.hpp"
#include "mat3.hpp"
#include <cmath>

#define DET(m, a, b, c, d) (m[a]*m[d]-m[b]*m[c])
#define DET3(mat, r, c) mat4::minor(mat, r, c)
#define EPSILON 0.000001

mat4::mat4(){
    for(int i=0; i<16; i++) this->data[i] = 0.0f;
}

mat4::mat4(
    float m00,float m01,float m02,float m03,
    float m10,float m11,float m12,float m13,
    float m20,float m21,float m22,float m23,
    float m30,float m31,float m32,float m33
){
    this->data[ 0] = m00; this->data[ 1] = m01; this->data[ 2] = m02; this->data[ 3] = m03;
    this->data[ 4] = m10; this->data[ 5] = m11; this->data[ 6] = m12; this->data[ 7] = m13;
    this->data[ 8] = m20; this->data[ 9] = m21; this->data[10] = m22; this->data[11] = m23;
    this->data[12] = m30; this->data[13] = m31; this->data[14] = m32; this->data[15] = m33;
}

mat4::mat4(const mat4& o){
    for(int i=0; i<16; i++) this->data[i] = o.data[i];
}

float mat4::determinant(){
    float a = this->data[ 0], b = this->data[ 1], c = this->data[ 2], d = this->data[ 3];
    float e = this->data[ 4], f = this->data[ 5], g = this->data[ 6], h = this->data[ 7];
    float i = this->data[ 8], j = this->data[ 9], k = this->data[10], l = this->data[11];
    float m = this->data[12], n = this->data[13], o = this->data[14], p = this->data[15];
    float da = mat3(f,g,h,j,k,l,n,o,p).determinant();
    float db = mat3(e,g,h,i,k,l,m,o,p).determinant();
    float dc = mat3(e,f,h,i,j,l,m,n,p).determinant();
    float dd = mat3(e,f,g,i,j,k,m,n,o).determinant();
    return a*da - b*db + c*dc - d*dd;
}

mat4& mat4::rotate(float xRad, float yRad, float zRad){
    float sx = std::sin(xRad), cx = std::cos(xRad);
    float sy = std::sin(yRad), cy = std::cos(yRad);
    float sz = std::sin(zRad), cz = std::cos(zRad);
    return (*this) * mat4(
                 cy*cz,         -sz*cy,     sy, 0,
              sx*sy*cz, cx*cz-sx*sy*sz, -sx*cy, 0,
        sx*sz-sy*cx*cz, sx*cz+sy*sz*cx,  cx*cy, 0,
                     0,              0,      0, 1
    );
}

mat4& mat4::rotateX(float rad){
    float s = std::sin(rad), c = std::cos(rad);
    return (*this) * mat4(
        1, 0, 0, 0,
        0, c,-s, 0,
        0, s, c, 0,
        0, 0, 0, 1
    );
}

mat4& mat4::rotateY(float rad){
    float s = std::sin(rad), c = std::cos(rad);
    return (*this) * mat4(
         c, 0, s, 0,
         0, 1, 0, 0,
        -s, 0, c, 0,
         0, 0, 0, 1
    );
}

mat4& mat4::rotateZ(float rad){
    float s = std::sin(rad), c = std::cos(rad);
    return (*this) * mat4(
        c,-s, 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

mat4& mat4::scale(float xScl, float yScl, float zScl){
    return (*this) * mat4(
        xScl,    0,    0, 0,
           0, yScl,    0, 0,
           0,    0, zScl, 0,
           0,    0,    0, 1
    );
}

mat4& mat4::scale(float scale){
    return this->scale(scale, scale, scale);
}

mat4& mat4::translate(float x, float y, float z){
    return (*this) * mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    );
}

mat4& mat4::operator *(const mat4& rhs){
    mat4 lhs = *this;
    for(int i=0, r=0; r<4; r++)
    for(int c=0; c<4; c++, i++){
        this->data[i] = 0.0f;
        for(int n=0; n<4; n++) this->data[i] += lhs.data[r*4+n] * rhs.data[n*4+c];
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const mat4& mat){
    for(int r=0; r<4; r++){
        for(int c=0; c<4; c++){
            out << ("%.4f", mat.data[r*4+c]);
            if(c < 3) out << " ";
        }
        if(r < 3) out << "\n";
    }
    return out;
}

mat4 mat4::identity(){
    return mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
}

mat4 mat4::invert(mat4& mat){
    float det = mat.determinant();
    if(std::abs(det) < EPSILON) return mat4::identity();
    det = 1.0f / det;
    mat4 M = mat4::minor(mat);
    for(int i=0; i<16; i++) M[i] *= i%2?-1:1 * det;
    return mat4::transpose(M);
}

mat4 mat4::minor(const mat4& mat){
    float a = mat.data[ 0], b = mat.data[ 1], c = mat.data[ 2], d = mat.data[ 3];
    float e = mat.data[ 4], f = mat.data[ 5], g = mat.data[ 6], h = mat.data[ 7];
    float i = mat.data[ 8], j = mat.data[ 9], k = mat.data[10], l = mat.data[11];
    float m = mat.data[12], n = mat.data[13], o = mat.data[14], p = mat.data[15];
    return mat4(
        DET3(mat,0,0), DET3(mat,0,1), DET3(mat,0,2), DET3(mat,0,3),
        DET3(mat,1,0), DET3(mat,1,1), DET3(mat,1,2), DET3(mat,1,3),
        DET3(mat,2,0), DET3(mat,2,1), DET3(mat,2,2), DET3(mat,2,3),
        DET3(mat,3,0), DET3(mat,3,1), DET3(mat,3,2), DET3(mat,3,3)
    );
}

float mat4::minor(const mat4& mat, int row, int col){
    mat3 ret;
    int rr = 0, cc = 0;
    for(int r=0; r<4; r++, rr++){
        if(r == row) { rr--; continue; }
        for(int c=0; c<4; c++, cc++){
            if(c == col) { cc--; continue; }
            ret[rr*3+cc] = mat.data[r*4+c];
        }
    }
    return ret.determinant();
}

#define DOT(a) -vec3::dot(a##axis, eye)
mat4 mat4::lookAt(vec3 eye, vec3 target, vec3 up){
    vec3 f = vec3::normalize(vec3::sub(eye, target));
    vec3 l = vec3::cross(up, f);
    vec3 u = vec3::cross(f, l);
    mat4 MR(
        l.x,l.y,l.z,0,
        u.x,u.y,u.z,0,
        f.x,f.y,f.z,0,
        eye.x, eye.y, eye.z,1
    );
    return MR;
}
#undef DOT

mat4 mat4::perspective(float fovRad, float aspect, float near, float far){
    float b = 1.0f / std::tan(fovRad / 2.0f),
        a = b / aspect,
        fan = far + near, fsn = far - near,
        c = -fan / fsn,
        d = -2 * far * near / fsn;
    return mat4(
        a, 0, 0, 0,
        0, b, 0, 0,
        0, 0, c, d,
        0, 0,-1, 0
    );
}

mat4 mat4::transpose(const mat4& mat){
    mat4 ret;
    for(int r=0; r<4; r++)
    for(int c=0; c<4; c++)
        ret[c*4+r] = mat.data[r*4+c];
    return ret;
}

#undef EPSILON
#undef DET3
#undef DET