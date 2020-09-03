#include "vec3.hpp"
#include <cmath>

#define DET(a, b, c, d) (a*d-b*c)
#define EPSILON 0.000001

vec3::vec3(){
    this->x = this->y = this->z = 0.0f;
}

vec3::vec3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3::vec3(const vec3& o){
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
}

std::ostream& operator <<(std::ostream& out, const vec3& vec){
    return out << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

vec3 vec3::add(const vec3& a, const vec3& b){
    return vec3(a.x+b.x, a.y+b.y, a.z+b.z);
}

vec3 vec3::cross(const vec3& a, const vec3& b){
    return vec3(
        +DET(a.y, a.z, b.y, b.z),
        -DET(a.x, a.z, b.x, b.z),
        +DET(a.x, a.y, b.x, b.y)
    );
}

float vec3::dot(const vec3& a, const vec3& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

float vec3::mag(const vec3& v){
    return std::sqrt(vec3::dot(v, v));
}

vec3 vec3::normalize(const vec3& v){
    float mag = vec3::mag(v);
    if(std::abs(mag) < EPSILON) return vec3(0, 0, 0);
    mag = 1.0f / mag;
    return vec3(v.x*mag, v.y*mag, v.z*mag);
}

vec3 vec3::sub(const vec3& a, const vec3& b){
    return vec3(a.x-b.x, a.y-b.y, a.z-b.z);
}

#undef EPSILON
#undef DET