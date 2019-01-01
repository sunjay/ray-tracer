#pragma once

#include "material.hpp"

// Lambertian (diffuse) material
class lambert : public material {
    // The albedo of a surface is the fraction of the incident sunlight that the
    // surface reflects.
    vec3 albedo;

public:
    lambert(const vec3 &albedo);

    virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const override;
};
