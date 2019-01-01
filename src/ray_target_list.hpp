#ifndef RAY_TARGET_LIST_HPP
#define RAY_TARGET_LIST_HPP

#include <vector>
#include <memory>

#include "ray_target.hpp"

class ray_target_list : public ray_target {
private:
    // ray_target is abstract, so we need it behind a pointer so we can do
    // dynamic dispatch
    std::vector<std::unique_ptr<ray_target>> targets;

public:
    ray_target_list();

    void push_back(ray_target *target);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};

#endif /* end of include guard: RAY_TARGET_LIST_HPP */
