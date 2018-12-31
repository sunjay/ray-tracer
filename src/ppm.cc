#include "vec3.hpp"

#include "ppm.hpp"

using std::endl;

const int MAX_COLOR = 255;

ppm_image::ppm_image(std::ostream &out, int nx, int ny): out{out}, remaining{nx * ny} {
    out << "P3" << endl;
    out << nx << ' ' << ny << endl;
    out << MAX_COLOR << endl;
}

void ppm_image::add(vec3 &rgb) {
    // Need the + 0.99 so we get the right rounding behaviour (int truncates)
    double max = ((double)MAX_COLOR) + 0.99;
    int ir = int(max * rgb.r());
    int ig = int(max * rgb.g());
    int ib = int(max * rgb.b());
    out << ir << ' ' << ig << ' ' << ib << endl;

    remaining -= 1;
}

void ppm_image::finish() {
    if (remaining > 0) {
        throw PPMIncomplete(remaining);
    }
    out.flush();
}
