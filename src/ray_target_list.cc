#include "ray_target_list.hpp"

ray_target_list::ray_target_list() {}

void ray_target_list::push_back(ray_target *target) {
    targets.push_back(std::unique_ptr<ray_target>(target));
}

bool ray_target_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double smallest_t = t_max;
    for (const auto &target : targets) {
        if (target->hit(r, t_min, smallest_t, temp_rec)) {
            hit_anything = true;
            smallest_t = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
