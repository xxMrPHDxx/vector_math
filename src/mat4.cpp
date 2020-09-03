#include "mat4.hpp"
#include "mat3.hpp"
#include "vec3.hpp"

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

mat4 mat4::lookAt(vec3 eye, vec3 center, vec3 up){
    vec3 zaxis = vec3::normalize(vec3::sub(center, eye));
    vec3 xaxis = vec3::normalize(vec3::cross(up, zaxis));
    vec3 yaxis = vec3::cross(zaxis, xaxis);
    return mat4(
        xaxis.x, yaxis.x, zaxis.x, 0,
        xaxis.y, yaxis.y, zaxis.y, 0,
        xaxis.z, yaxis.z, zaxis.z, 0,
        xaxis.x*eye.x+xaxis.y*eye.y+xaxis.z*eye.z,
        yaxis.x*eye.x+yaxis.y*eye.y+yaxis.z*eye.z,
        zaxis.x*eye.x+zaxis.y*eye.y+zaxis.z*eye.z,
        1
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