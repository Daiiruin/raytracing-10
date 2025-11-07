#pragma once
#include "../scene/Scene.hpp"
#include "../core/Ray.hpp"
#include "../core/HitRecord.hpp"

struct Renderer {
    int maxDepth;
    void render(const Scene& scene);
};