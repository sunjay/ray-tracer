#include "ray_target_list.hpp"

ray_target_list::ray_target_list() {}
ray_target_list::ray_target_list(std::initializer_list<ray_target *> target_ptrs):
    size{target_ptrs.size()}, targets{new std::unique_ptr<ray_target>[size]} {

    size_t i = 0;
    for (ray_target *ptr : target_ptrs) {
        targets[i] = std::unique_ptr<ray_target>(ptr);
        i += 1;
    }
}

ray_target_list::~ray_target_list() {
    delete [] targets;
}

bool ray_target_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double smallest_t = t_max;
    for (size_t i = 0; i < size; i++) {
        const auto &target = targets[i];
        if (target->hit(r, t_min, smallest_t, temp_rec)) {
            hit_anything = true;
            smallest_t = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
