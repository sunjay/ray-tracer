#include "ray_target.hpp"

#include "lambert.hpp"

lambert::lambert(const vec3 &albedo): albedo{albedo} {}

bool lambert::scatter(const ray &, const hit_record &rec, scatter_record &srec) const {
    // Diffuse material - absorbes the color of things around it and mixes
    // in its own color.
    // Pick a random point `target` from the unit radius sphere that is
    // tangent to the hit point
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    // Send a ray from p to the random point `target`. The sphere has center
    // (p + N).
    // Absorb the color of the target but blend it with the color of this
    // sphere by multiplying it by 0.5. We absorb 50% of the energy on
    // each bounce.
    srec.scattered = ray(rec.p, target-rec.p);
    srec.attenuation = albedo;
    return true;
}
