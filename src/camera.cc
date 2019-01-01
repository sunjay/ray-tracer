#include "camera.hpp"

camera::camera():
    // Start position where scanning begins
    lower_left_corner(-2.0, -1.0, -1.0),
    // Width of the rectangle to scan
    horizontal(4.0, 0.0, 0.0),
    // Height of the rectangle to scan
    vertical(0.0, 2.0, 0.0),
    // Origin of the ray that is used for scanning
    origin(0.0, 0.0, 0.0) {}

ray camera::ray_for(double u, double v) const {
    return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}
