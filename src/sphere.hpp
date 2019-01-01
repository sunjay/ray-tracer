#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "vec3.hpp"
#include "ray_target.hpp"

class sphere : public ray_target {
    vec3 center;
    double radius;

public:
    sphere();
    sphere(vec3 center, double radius);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};

#endif /* end of include guard: SPHERE_HPP */
