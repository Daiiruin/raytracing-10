#pragma once
#include "Object.hpp"
#include <cmath>

struct Cube : Object {
    Vec3 minCorner;
    Vec3 maxCorner;

    Cube(const Vec3& minC, const Vec3& maxC, const Material& m) {
        minCorner = minC;
        maxCorner = maxC;
        mat = m;
    }

    std::optional<Hit> intersect(const Ray& r, double tMin, double tMax) const override {
        double t0 = tMin, t1 = tMax;

        for (int i = 0; i < 3; i++) {
            double orig = (i == 0 ? r.o.x : (i == 1 ? r.o.y : r.o.z));
            double dir  = (i == 0 ? r.d.x : (i == 1 ? r.d.y : r.d.z));
            double minV = (i == 0 ? minCorner.x : (i == 1 ? minCorner.y : minCorner.z));
            double maxV = (i == 0 ? maxCorner.x : (i == 1 ? maxCorner.y : maxCorner.z));

            double invD = 1.0 / dir;
            double tNear = (minV - orig) * invD;
            double tFar  = (maxV - orig) * invD;

            if (invD < 0) std::swap(tNear, tFar);

            t0 = std::max(t0, tNear);
            t1 = std::min(t1, tFar);

            if (t1 <= t0) return {};
        }

        Hit h;
        h.t = t0;
        h.p = r.o + r.d * h.t;

        const double eps = 1e-4;
        if (fabs(h.p.x - minCorner.x) < eps) h.n = {-1,0,0};
        else if (fabs(h.p.x - maxCorner.x) < eps) h.n = {1,0,0};
        else if (fabs(h.p.y - minCorner.y) < eps) h.n = {0,-1,0};
        else if (fabs(h.p.y - maxCorner.y) < eps) h.n = {0,1,0};
        else if (fabs(h.p.z - minCorner.z) < eps) h.n = {0,0,-1};
        else if (fabs(h.p.z - maxCorner.z) < eps) h.n = {0,0,1};

        h.mat = &mat;
        return h;
    }
};
