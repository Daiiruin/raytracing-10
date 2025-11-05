#pragma once
#include <optional>
#include "../core/Ray.hpp"
#include "../core/HitRecord.hpp"

struct Object {
    Material material;
    virtual ~Object() = default;
    virtual std::optional<HitRecord> intersect(
        const Ray& ray, // Rayon à tester
        double minDistance, // Distance minimale à considérer
        double maxDistance // Distance maximale à considérer
    ) const = 0;
};
