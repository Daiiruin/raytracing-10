#pragma once
#include "Vec3.hpp"

struct Material {
    Vec3 color{1,1,1};
    double diffuse=0.7;
    double specular=0.5;
    double shininess=32.0;
    double reflectivity=0.0;
};
