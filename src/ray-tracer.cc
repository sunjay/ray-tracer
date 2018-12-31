#include <iostream>

#include "vec3.hpp"
#include "ppm.hpp"

using namespace std;

int main() {
    int nx = 200;
    int ny = 100;
    ppm_image img(cout, nx, ny);
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            img.add(col);
        }
    }
    img.finish();

    return 0;
}
