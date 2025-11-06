#pragma once
#include <optional>
#include "../core/Ray.hpp"
#include "../core/Hit.hpp"

struct Object {
    Material mat;
    virtual ~Object() = default;
    virtual std::optional<Hit> intersect(const Ray& r, double tMin, double tMax) const = 0;
};
