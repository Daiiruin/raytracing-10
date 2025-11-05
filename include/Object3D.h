#pragma once
#include "Ray.h"
#include "Material.h"

class Object3D {
public:
    Material material;
    virtual bool intersect(const Ray& ray, double& t) const = 0;
    virtual Vec3 getNormal(const Vec3& p) const = 0;
    virtual ~Object3D() = default;
};
