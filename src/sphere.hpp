#pragma once

#include <memory>

#include "vec3.hpp"
#include "ray_target.hpp"

class material;

class sphere : public ray_target {
    vec3 center;
    double radius;
    std::unique_ptr<material> mat;

public:
    sphere(material *mat);
    sphere(vec3 center, double radius, material *mat);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};
