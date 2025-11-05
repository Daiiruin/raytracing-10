#pragma once
#include <vector>
#include "Object3D.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

class Scene {
public:
    std::vector<Object3D*> objects;
    void add(Object3D* obj);
    bool intersect(const Ray& ray, Vec3& hitPoint, Vec3& normal, Material& mat) const;
    ~Scene();
};
