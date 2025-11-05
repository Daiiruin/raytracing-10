#include "Plane.h"
#include <cmath>

Plane::Plane(const Vec3& n, double d, const Material& m) {
    normal = n;
    this->d = d;
    material = m;
}

bool Plane::intersect(const Ray& r, double& t) const {
    double denom = normal.dot(r.direction);
    if (fabs(denom) < 1e-6) return false;
    t = -(normal.dot(r.origin) + d)/denom;
    return t >= 1e-4;
}

Vec3 Plane::getNormal(const Vec3& p) const {
    return normal;
}
