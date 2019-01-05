#pragma once

#include <random>

inline double rand_double() {
    static thread_local std::default_random_engine rng;
    std::uniform_real_distribution<double> dist;
    return dist(rng);
}
