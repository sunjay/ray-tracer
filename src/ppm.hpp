#pragma once

#include <iostream>
#include <exception>

class vec3;

// Streams PPM image data to the given stream
class ppm_image {
    std::ostream &out;
    int remaining;

public:
    struct PPMIncomplete : public std::exception {
        int remaining;

        PPMIncomplete(int remaining): remaining{remaining} {}
        const char * what () const throw () {
            return "Could not complete writing PPM file, not enough colors provided";
        }
    };

    ppm_image(std::ostream &out, int nx, int ny);
    // Add an RGB color to the output image
    // Each R,G,B value is expected to be in the range 0.0 to 1.0
    void add(const vec3 &rgb);
    // Finish writing the image data
    // Throws PPMIncomplete if not enough colors were provided
    void finish();
};
