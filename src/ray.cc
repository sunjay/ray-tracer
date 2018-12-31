#include "ray.hpp"

ray::ray() {}
ray::ray(const vec3 &a, const vec3 &b): a{a}, b{b} {}

vec3 ray::origin() const {
    return a;
}

vec3 ray::direction() const {
    return b;
}

vec3 ray::at(double t) const {
    return a + b * t;
}
