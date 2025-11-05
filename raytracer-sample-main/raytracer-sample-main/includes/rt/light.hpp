#pragma once
#include "math.hpp"

namespace rt {

struct LightDir {
    Vec3 dir = normalize({-0.6, 1.0, -0.35}); // direction vers la scène
    double ambient = 0.04;
    double specStrength = 1.2;
    double shininess = 200.0;

    // soft shadows
    double cone_angle_deg = 4.0;
    int shadow_samples = 16;
};

}
