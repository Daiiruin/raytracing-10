#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "Constants.h"

class Camera {
public:
    Vec3 position;
    Vec3 forward;
    Vec3 right;
    Vec3 up;
    double fov;

    Camera(const Vec3& pos, const Vec3& lookAt, double fovDeg);
    Ray generateRay(int x, int y, int width, int height) const;
};
