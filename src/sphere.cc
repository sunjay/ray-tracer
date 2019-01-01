#include <cmath> // sqrt

#include "ray.hpp"

#include "sphere.hpp"

sphere::sphere() {}
sphere::sphere(vec3 center, double radius): center{center}, radius{radius} {}

// Returns the color of the sphere at the given point based on the angle that
// this point represents on the sphere. Mappings:
// * red = x-value
// * green = y-value
// * blue = z-value
vec3 sphere_normal_map_color(const hit_record &rec) {
    return rec.normal.to_unit_range();
}

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
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

    if (discriminant < 0) {
        return false;
    }

    // Try to return the smallest solution within the range
    double t = (-b - sqrt(discriminant)) / (2.0*a);
    if (t > t_min && t < t_max) {
        rec.t = t;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        rec.color = sphere_normal_map_color(rec);
        return true;
    }
    // Try other solution
    t = (-b + sqrt(discriminant)) / (2.0*a);
    if (t > t_min && t < t_max) {
        rec.t = t;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        rec.color = sphere_normal_map_color(rec);
        return true;
    }

    // No solution within range
    return false;
}
