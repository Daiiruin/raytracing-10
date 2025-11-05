#pragma once
#include "math.hpp"
#include "ray.hpp"

namespace rt {

struct Camera {
    Vec3 position{0.0, 0.6, -0.6};
    double fov_deg = 65.0;

    Ray getWorldRay(double px, double py, int W, int H) const {
        double aspect = double(W)/H;
        double fov = fov_deg*PI/180.0;
        double sx = ((px+0.5)/W*2.0-1.0) * std::tan(fov/2.0) * aspect;
        double sy = ((py+0.5)/H*2.0-1.0) * std::tan(fov/2.0);
        Vec3 d = normalize({sx, sy, 1.0});
        return {position, d};
    }
};

}
