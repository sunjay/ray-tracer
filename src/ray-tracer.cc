#include <cstdlib> // drand48
#include <limits> // std::numeric_limits

#include "vec3.hpp"
#include "ppm.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "ray_target_list.hpp"
#include "sphere.hpp"
#include "lambert.hpp"
#include "metal.hpp"

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
vec3 color(const ray &r, const ray_target &world, int depth) {
    hit_record rec;
    // Some reflected rays hit the object they are reflecting off of, so we need
    // to ignore hits very near zero. Hence, 0.001
    if (world.hit(r, 0.001, numeric_limits<double>::max(), rec)) {
        scatter_record srec;
        if (depth < 50 && rec.mat->scatter(r, rec, srec)) {
            return srec.attenuation * color(srec.scattered, world, depth+1);
        }
        // default if max-depth has been reached
        return vec3(0, 0, 0);
    }

    // If nothing else is hit, return the background
    return background_color(r);
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100; // number of samples for antialiasing
    ppm_image img(cout, nx, ny);

    ray_target_list world {
        new sphere(vec3(0, 0, -1), 0.5, new lambert(vec3(0.8, 0.3, 0.3))),
        new sphere(vec3(0, -100.5, -1), 100, new lambert(vec3(0.8, 0.8, 0.0))),
        new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3)),
        new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1.0))
    };

    camera cam;

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col;
            // perform antialiasing: average many samples of rays randomly
            // around the actual pixel we are focusing on
            for (int s = 0; s < ns; s++) {
                double u = double(i + drand48()) / double(nx);
                double v = double(j + drand48()) / double(ny);
                // Cast a ray from the ray origin to wards the current position
                // being scanned
                ray r = cam.ray_for(u, v);
                col += color(r, world, 0);
            }

            col /= double(ns);
            // Correcting for gamma correction in image viewers. Using gamma 2
            // which means raising to the power of 1/gamma = 1/2
            col = col.to_sqrt();
            img.add(col);
        }
    }
    img.finish();

    return 0;
}
