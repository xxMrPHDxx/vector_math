#ifndef VEC4_HPP
#define VEC4_HPP

class vec4 {
public:
    float x, y, z, w;
    vec4();
    vec4(float, float, float, float);
    vec4(const vec4&);
};

#endif