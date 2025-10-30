#pragma once
#include "../scene/Scene.hpp"
#include "../core/Ray.hpp"
#include "../core/Hit.hpp"

struct Renderer {
    int maxDepth=3;
    void render(const Scene& scene);
};
