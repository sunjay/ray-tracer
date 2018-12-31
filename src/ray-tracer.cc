#include <iostream>

#include "vec3.hpp"
#include "ppm.hpp"
#include "ray.hpp"

using namespace std;

// Computes the color seen in the direction of the ray.
// Computes what this ray intersects with and the color of that intersection point.
vec3 color(const ray &r) {
    vec3 unit_direction = r.direction().to_unit();
    // Just return the background for now
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 200;
    int ny = 100;
    ppm_image img(cout, nx, ny);

    // Start position where scanning begins
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    // Width of the rectangle to scan
    vec3 horizontal(4.0, 0.0, 0.0);
    // Height of the rectangle to scan
    vec3 vertical(0.0, 2.0, 0.0);
    // Origin of the ray that is used for scanning
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            // Cast a ray from the ray origin to wards the current position
            // being scanned
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);

            img.add(col);
        }
    }
    img.finish();

    return 0;
}
