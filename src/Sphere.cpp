#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Vec3& c, double r, const Material& m) {
    center = c;
    radius = r;
    material = m;
}

bool Sphere::intersect(const Ray& r, double& t) const {
    Vec3 oc = r.origin - center;
    double b = 2.0 * oc.dot(r.direction);
    double c = oc.dot(oc) - radius*radius;
    double disc = b*b - 4*c;
    if (disc < 0) return false;
    disc = sqrt(disc);
    double t0 = (-b - disc)/2;
    double t1 = (-b + disc)/2;
    t = (t0 > 1e-4) ? t0 : t1;
    return t > 1e-4;
}

Vec3 Sphere::getNormal(const Vec3& p) const {
    return (p - center).normalized();
}
