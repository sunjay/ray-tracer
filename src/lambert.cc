#include <random> // std::uniform_real_distribution

#include "ray_target.hpp"

#include "lambert.hpp"

using namespace std;

lambert::lambert(const vec3 &albedo): albedo{albedo} {}

// Returns a random coordinate on the surface of a unit-radius sphere
vec3 random_in_unit_sphere() {
    // Rejection method: try to generate a point within the volume of the unit
    // cube and reject if not on sphere
    std::default_random_engine rng;
    uniform_real_distribution<double> dist; // uniform, 0.0 <= x < 1.0

    vec3 p;
    do {
        p = 2.0*vec3(dist(rng), dist(rng), dist(rng)) - vec3(1, 1, 1);
    } while (p.square_length() >= 1.0);
    return p;
}

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
