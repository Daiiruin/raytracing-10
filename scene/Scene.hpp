#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../core/Vec3.hpp"
#include "../objects/Object.hpp"

struct PointLight { Vec3 pos,intensity; };

struct Scene {
    int width=500, height=400;
    std::string output="output.png";
    Vec3 camPos{0,0,0}, camLook{0,0,-1}, camUp{0,1,0};
    double fov=45.0;
    Vec3 ambient{0.1,0.1,0.1};
    std::vector<PointLight> lights;
    std::vector<std::unique_ptr<Object>> objects;
};
