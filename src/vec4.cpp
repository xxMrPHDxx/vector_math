#include "vec4.hpp"

vec4::vec4(){
    this->x = this->y = this->z = this->w = 0.0f;
}

vec4::vec4(float x, float y, float z, float w){
    this->x = x; this->y = y; this->z = z; this->w = w;
}

vec4::vec4(const vec4& o){
    this->x = o.x; this->y = o.y; this->z = o.z; this->w = o.w;
}

std::ostream& operator <<(std::ostream& out, const vec4& vec){
    return out << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}