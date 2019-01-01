#ifndef RAY_TARGET_HPP
#define RAY_TARGET_HPP

#include "vec3.hpp"

class ray;

struct hit_record {
    // The smallest positive value of t for which the given ray intersects the
    // target.
    double t;
    vec3 p;
    vec3 normal;
    vec3 color;
};

class ray_target {
public:
    // Returns true if this target is hit by the given ray and the t value is
    // within the given range.
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif /* end of include guard: RAY_TARGET_HPP */
