#pragma once

#include "material.hpp"

// Metal (smooth, reflective)
class metal : public material {
    // The albedo of a surface is the fraction of the incident sunlight that the
    // surface reflects.
    vec3 albedo;
    // Randomize the reflected direction using a small sphere and choosing a new
    // endpoint for the ray. Bigger sphere = fuzzier reflections.
    // max radius = 1
    double fuzz;
public:
    metal(const vec3 &albedo, double fuzz);

    virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const override;
};
