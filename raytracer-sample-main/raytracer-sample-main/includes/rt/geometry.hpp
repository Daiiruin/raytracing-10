#pragma once
#include "math.hpp"
#include "ray.hpp"

namespace rt {

struct Sphere { Vec3 c; double r; Vec3 color; };

struct Hit {
    double t = 1e30;
    Vec3 p, n, color;
    bool hit = false;
};

// Sphere
inline bool hitSphere(const Ray& r, const Sphere& s, Hit& h) {
    Vec3 oc = r.o - s.c;
    double a = dot(r.d, r.d);
    double b = 2.0*dot(oc, r.d);
    double c = dot(oc, oc) - s.r*s.r;
    double disc = b*b - 4*a*c;
    if (disc < 0) return false;
    double sd = std::sqrt(disc);
    double t1 = (-b - sd) / (2*a);
    double t2 = (-b + sd) / (2*a);
    double t  = (t1 > EPS) ? t1 : (t2 > EPS ? t2 : 0.0);
    if (t <= EPS || t >= h.t) return false;
    h.t = t; h.hit = true;
    h.p = r.o + r.d*t;
    h.n = normalize(h.p - s.c);
    h.color = s.color;
    return true;
}

// Plane y=0 checker
inline bool hitPlaneChecker(const Ray& r, Hit& h, double tile=0.9,
                            Vec3 colA={0.92,0.92,0.92}, Vec3 colB={0.08,0.08,0.08}) {
    if (std::fabs(r.d.y) < 1e-6) return false;
    double t = -r.o.y / r.d.y;
    if (t <= EPS || t >= h.t) return false;
    Vec3 p = r.o + r.d*t;
    int cx = int(std::floor(p.x/tile));
    int cz = int(std::floor(p.z/tile));
    bool odd = (cx + cz) & 1;
    h.t = t; h.hit = true;
    h.p = p; h.n = {0,1,0};
    h.color = odd ? colB : colA;
    return true;
}

}
