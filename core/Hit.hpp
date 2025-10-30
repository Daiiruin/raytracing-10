#pragma once
#include "Vec3.hpp"
#include "Material.hpp"

struct Hit {
    double t;
    Vec3 p;
    Vec3 n;
    const Material* mat;
};
