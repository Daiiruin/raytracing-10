#include "Scene.h"

void Scene::add(Object3D* obj) {
    objects.push_back(obj);
}

bool Scene::intersect(const Ray& ray, Vec3& hitPoint, Vec3& normal, Material& mat) const {
    double tNear = 1e9;
    bool hit = false;
    for (auto obj : objects) {
        double t;
        if (obj->intersect(ray, t) && t < tNear) {
            tNear = t;
            hitPoint = ray.origin + ray.direction * t;
            normal = obj->getNormal(hitPoint);
            mat = obj->material;
            hit = true;
        }
    }
    return hit;
}

Scene::~Scene() {
    for (auto o : objects) delete o;
}
