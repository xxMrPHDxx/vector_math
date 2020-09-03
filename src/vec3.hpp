#ifndef VEC3_HPP
#define VEC3_HPP

#include <ostream>

class vec3 {
public:
    float x, y, z;
    vec3();
    vec3(float, float, float);
    vec3(const vec3&);
    bool operator ==(const vec3&);
    bool operator !=(const vec3&);
    friend std::ostream& operator <<(std::ostream&, const vec3&);
    static vec3 add(const vec3&, const vec3&);
    static vec3 cross(const vec3&, const vec3&);
    static float dot(const vec3&, const vec3&);
    static float mag(const vec3&);
    static vec3 normalize(const vec3&);
    static vec3 sub(const vec3&, const vec3&);
};

#endif