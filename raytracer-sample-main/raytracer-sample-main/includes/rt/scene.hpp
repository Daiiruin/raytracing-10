#pragma once
#include "geometry.hpp"
#include "material.hpp"

namespace rt {

struct Scene {
    Sphere sphere;
    // plane y=0
    double tile = 0.9;
    Vec3 colA{0.92,0.92,0.92}, colB{0.08,0.08,0.08};
    double reflectivity_plane  = 0.4;
    double reflectivity_sphere = 0.15;
};

// Intersections + matériaux
inline bool intersectScene(const Ray& r, const Scene& sc, Hit& h, Material& mat) {
    bool any = false;

    Hit hp = h;
    if (hitPlaneChecker(r, hp, sc.tile, sc.colA, sc.colB)) {
        Material m; m.color = hp.color; m.reflectivity = sc.reflectivity_plane;
        h = hp; mat = m; any = true;
    }

    Hit hs = h;
    if (hitSphere(r, sc.sphere, hs)) {
        Material m; m.color = hs.color; m.reflectivity = sc.reflectivity_sphere;
        if (!any || hs.t < h.t) { h = hs; mat = m; any = true; }
    }
    return any;
}

}
