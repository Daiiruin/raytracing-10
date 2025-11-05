#pragma once
#include "Vec3.h"

class Material {
public:
    Vec3 color;
    double reflectivity;
    Material(const Vec3& c=Vec3(1,1,1), double r=0);
};
