#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../core/Vec3.hpp"
#include "../objects/Object.hpp"

struct PointLight {
    Vec3 position, intensity;
};

struct Scene {
    int width = 500;
    int height = 400;
    std::string output = "output.png";

    Vec3 cameraPosition { 0.0, 0.0, 0.0 };
    Vec3 cameraTarget { 0.0, 0.0, -1.0 };
    Vec3 cameraUp { 0.0, 1.0, 0.0 };
    double fov  = 45.0;

    Vec3 ambientLightIntensity { 0.1, 0.1, 0.1 };

    std::vector<PointLight> lights;
    std::vector<std::unique_ptr<Object>> objects;
};
