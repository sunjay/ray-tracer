#include "random.hpp"

#include "material.hpp"

// Returns a random coordinate on the surface of a unit-radius sphere
vec3 random_in_unit_sphere() {
    // Rejection method: try to generate a point within the volume of the unit
    // cube and reject if not on sphere
    vec3 p;
    do {
        p = 2.0*vec3(rand_double(), rand_double(), rand_double()) - vec3(1, 1, 1);
    } while (p.square_length() >= 1.0);
    return p;
}
