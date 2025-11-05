#pragma once
#include "Object3D.h"

class Plane : public Object3D {
public:
    Vec3 normal;
    double d;
    Plane(const Vec3& n, double d, const Material& m);

    bool intersect(const Ray& r, double& t) const override;
    Vec3 getNormal(const Vec3& p) const override;
};
