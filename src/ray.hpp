#pragma once

#include "vec3.hpp"

class ray {
    vec3 a;
    vec3 b;
public:
    ray();
    ray(const vec3 &a, const vec3 &b);

    vec3 origin() const;
    vec3 direction() const;

    vec3 at(double t) const;
};
