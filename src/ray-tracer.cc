#include <iostream>

#include "vec3.hpp"
#include "ppm.hpp"
#include "ray.hpp"

using namespace std;

bool hit_sphere(const vec3 &center, double radius, const ray &r) {
    // Equation for sphere: x*x + y*y + z*z = R*R
    // With arbitrary center: (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz) = R*R
    // In vector form: (p - c).dot(p - c) = R*R where p = (x, y, z), c = (cx, cy, cz)
    // To check if ray intersects sphere, let p = r where r = a + t*b
    // This gives us: (r - c).dot(r - c) = R*R
    // Substituting: (a + t*b - c).dot(a + t*b - c) = R*R
    // Expanding: t*t*b.dot(b) + 2*t*b.dot(a-c) + (a-c).dot(a-c) - R*R = 0
    // From the quadratic formula, we get the discriminant b*b - 4*a*c
    // This tells us the number of solutions and we can interpret it as the
    // number of intersections. As long as the discriminant tells us there are
    // at least two intersections, the ray passes through the sphere. One
    // intersection means that the ray just hits on the edge.
    vec3 oc = r.origin() - center;
    double a = r.direction().dot(r.direction());
    double b = 2.0 * oc.dot(r.direction());
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b*b - 4*a*c;
    return discriminant > 0;
}

// Computes the color seen in the direction of the ray.
// Computes what this ray intersects with and the color of that intersection point.
vec3 color(const ray &r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return vec3(0, 1, 1);
    }

    // If nothing else is hit, return the background

    // Make into unit vector so -1.0 < y < 1.0
    vec3 unit_direction = r.direction().to_unit();
    // Scales the y value so 0.0 < t < 1.0
    double t = 0.5*(unit_direction.y() + 1.0);
    // This is a linear interpolation (lerp) which always has the form:
    // blended_value = (1 - t) * start_value + t*end_value with t = 0.0 to 1.0
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
            double u = double(i) / double(nx);
            double v = double(j) / double(ny);
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
