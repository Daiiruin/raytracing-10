#pragma once
#include "Object.hpp"

struct Sphere : Object {
    Vec3 c; double R;
    Sphere(const Vec3& c_, double R_, const Material& m){ c=c_; R=R_; mat=m; }

    std::optional<Hit> intersect(const Ray& r,double tMin,double tMax) const override {
        Vec3 oc=r.o-c; double a=dot(r.d,r.d); double b=2*dot(oc,r.d);
        double c2=dot(oc,oc)-R*R; double disc=b*b-4*a*c2; if(disc<0) return {};
        double s=std::sqrt(disc); double t=(-b-s)/(2*a);
        if(t<tMin||t>tMax) t=(-b+s)/(2*a); if(t<tMin||t>tMax) return {};
        Hit h{t,r.o+r.d*t,normalize((r.o+r.d*t)-c),&mat}; return h;
    }
};
