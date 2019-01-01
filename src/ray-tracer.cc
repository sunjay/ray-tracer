#include <random> // std::uniform_real_distribution
#include <limits> // std::numeric_limits

#include "vec3.hpp"
#include "ppm.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "ray_target_list.hpp"
#include "sphere.hpp"

using namespace std;

// Returns the color of the background that the given ray intersects with
vec3 background_color(const ray &r) {
    // Make into unit vector so -1.0 < y < 1.0
    vec3 unit_direction = r.direction().to_unit();
    // Scales the y value so 0.0 < t < 1.0
    double t = 0.5*(unit_direction.y() + 1.0);
    // This is a linear interpolation (lerp) which always has the form:
    // blended_value = (1 - t) * start_value + t*end_value with t = 0.0 to 1.0
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

// Computes the color seen in the direction of the ray.
// Computes what this ray intersects with and the color of that intersection point.
vec3 color(const ray &r, const ray_target &world) {
    hit_record rec;
    if (world.hit(r, 0.0, numeric_limits<double>::max(), rec)) {
        return rec.color;
    }

    // If nothing else is hit, return the background
    return background_color(r);
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100; // number of samples for antialiasing
    ppm_image img(cout, nx, ny);

    ray_target_list world;
    world.push_back(new sphere(vec3(0, 0, -1), 0.5));
    world.push_back(new sphere(vec3(0, -100.5, -1), 100));

    camera cam;

    std::default_random_engine rng;
    uniform_real_distribution<double> dist; // uniform, 0.0 <= x < 1.0
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col;
            // perform antialiasing: average many samples of rays randomly
            // around the actual pixel we are focusing on
            for (int s = 0; s < ns; s++) {
                double u = (double(i) + dist(rng)) / double(nx);
                double v = (double(j) + dist(rng)) / double(ny);
                // Cast a ray from the ray origin to wards the current position
                // being scanned
                ray r = cam.ray_for(u, v);
                col += color(r, world);
            }

            col /= double(ns);
            img.add(col);
        }
    }
    img.finish();

    return 0;
}
