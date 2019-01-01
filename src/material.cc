#include <random> // std::uniform_real_distribution

#include "material.hpp"

// Returns a random coordinate on the surface of a unit-radius sphere
vec3 random_in_unit_sphere() {
    // Rejection method: try to generate a point within the volume of the unit
    // cube and reject if not on sphere
    std::default_random_engine rng;
    std::uniform_real_distribution<double> dist; // uniform, 0.0 <= x < 1.0

    vec3 p;
    do {
        p = 2.0*vec3(dist(rng), dist(rng), dist(rng)) - vec3(1, 1, 1);
    } while (p.square_length() >= 1.0);
    return p;
}
