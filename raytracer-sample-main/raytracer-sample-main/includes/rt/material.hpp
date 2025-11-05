#pragma once
#include "math.hpp"

namespace rt {

struct Material {
    Vec3 color{1,1,1};
    double reflectivity = 0.0; // 0 = mat, 1 = miroir
};

}
