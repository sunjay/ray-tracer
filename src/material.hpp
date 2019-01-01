#pragma once

#include "vec3.hpp"
#include "ray.hpp"

class hit_record;

struct scatter_record {
    // The amount to attenuate/reduce the ray after being scattered
    vec3 attenuation;
    ray scattered;
};

class material {
public:
    // Returns true if the ray should be scattered from this material. Returns
    // false if the ray was absorbed. The scatter record contains information
    // about the scattering that should occur.
    virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const = 0;
};
