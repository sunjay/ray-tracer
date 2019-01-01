#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

class camera {
    // Start position where scanning begins
    vec3 lower_left_corner;
    // Width of the rectangle to scan
    vec3 horizontal;
    // Height of the rectangle to scan
    vec3 vertical;
    // Origin of the ray that is used for scanning
    vec3 origin;
public:
    camera();

    ray ray_for(double u, double v) const;
};

#endif /* end of include guard: CAMERA_HPP */
