#pragma once
#include "Object3D.h"

class Sphere : public Object3D {
public:
    Vec3 center;
    double radius;
    Sphere(const Vec3& c, double r, const Material& m);

    bool intersect(const Ray& r, double& t) const override;
    Vec3 getNormal(const Vec3& p) const override;
};
