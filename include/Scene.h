#pragma once
#include <vector>
#include "Object3D.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

class Scene {
public:
    std::vector<Object3D*> objects; // Contient tous les objets de la scène. 
                                  //Chaque objet est un pointeur vers une instance d’Object3D (ou d’une de ses classes dérivées comme Sphere, Plane, etc.).
    void add(Object3D* obj)  ;     //Scene scene; scene.add(new Sphere(Vec3(0,0,-5), 1, Material(Vec3(1,0,0), 0.5)))
   
    bool intersect(const Ray& ray, Vec3& hitPoint, Vec3& normal, Material& mat) const;
    ~Scene();
};
