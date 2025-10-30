#pragma once
#include "Object.hpp"

struct Cone : Object {
    Vec3 apex;     
    double height; 
    double radius;
    Vec3 baseCenter;

    Cone(const Vec3& baseC, double r, double h, const Material& m) {
        baseCenter = baseC;
        radius = r;
        height = h;
        apex = baseC + Vec3(0, h, 0);
        mat = m;
    }

    std::optional<Hit> intersect(const Ray& ray, double tMin, double tMax) const override {
        Vec3 co = ray.o - apex;
        double k = radius / height;
        k = k * k;

        double dx = ray.d.x, dy = ray.d.y, dz = ray.d.z;
        double ox = co.x, oy = co.y, oz = co.z;

        double A = dx*dx + dz*dz - k*dy*dy;
        double B = 2*(dx*ox + dz*oz - k*dy*oy);
        double C = ox*ox + oz*oz - k*oy*oy;

        double disc = B*B - 4*A*C;
        if (disc < 0) return {};

        double sqrtDisc = std::sqrt(disc);
        double t1 = (-B - sqrtDisc) / (2*A);
        double t2 = (-B + sqrtDisc) / (2*A);

        double t = (t1 > tMin && t1 < tMax) ? t1 : ((t2 > tMin && t2 < tMax) ? t2 : -1);
        if (t < 0) return {};

        Vec3 p = ray.o + ray.d * t;

        if (p.y < baseCenter.y || p.y > apex.y) return {};

        Vec3 v = normalize(Vec3(p.x, (radius/height)*std::sqrt(p.x*p.x + p.z*p.z), p.z));
        Hit hit{t, p, v, &mat};
        return hit;
    }
};
