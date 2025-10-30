#pragma once
#include "Object.hpp"

struct Plane : Object {
    Vec3 n; double d;
    Plane(const Vec3& n_, double d_, const Material& m){ n=normalize(n_); d=d_; mat=m; }

    std::optional<Hit> intersect(const Ray& r,double tMin,double tMax) const override {
        double denom=dot(n,r.d); if(fabs(denom)<1e-6) return {};
        double t=-(dot(n,r.o)+d)/denom;
        if(t<tMin||t>tMax) return {}; Hit h{t,r.o+r.d*t,n,&mat}; return h;
    }
};
