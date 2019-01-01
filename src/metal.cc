#include "ray_target.hpp"

#include "metal.hpp"

metal::metal(const vec3 &albedo): albedo{albedo} {}

// Returns the reflection of v off a surface with normal n.
static vec3 reflect(const vec3 &v, const vec3 &n) {
    // n is a unit vector. v points into the surface, n points out of it.
    // How does this work??
    return v - 2*v.dot(n)*n;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const {
    vec3 reflected = reflect(r_in.direction().to_unit(), rec.normal);
    srec.scattered = ray(rec.p, reflected);
    srec.attenuation = albedo;
    // dot product is < 0 when angle > 90 degrees and > 0 otherwise
    return srec.scattered.direction().dot(rec.normal) > 0;
}
