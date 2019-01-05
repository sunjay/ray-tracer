#pragma once

#include <initializer_list>
#include <memory>

#include "ray_target.hpp"

class ray_target_list : public ray_target {
private:
    size_t size;
    // ray_target is abstract, so we need it behind a pointer so we can do
    // dynamic dispatch
    std::unique_ptr<ray_target> *targets;

public:
    ray_target_list();
    ray_target_list(std::initializer_list<ray_target *> target_ptrs);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    ~ray_target_list();
};
