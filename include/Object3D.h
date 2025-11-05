#pragma once
#include "Ray.h"
#include "Material.h"

class Object3D { // Object3D est une classe de base abstraite, c’est-à-dire qu’on ne peut pas créer directement un objet de ce type.
public:
    Material material;// Chaque objet 3D possède un matériau (material), qui décrit la façon dont il interagit avec la lumière (par exemple, s’il est mat, brillant, transparent, etc.).
   
   /*Cette fonction teste si un rayon (ray) intersecte l’objet.
     Si c’est le cas : Elle retourne true.
     Elle met à jour t, la distance entre l’origine du rayon et le point d’intersection.
     Le = 0 signifie que c’est une méthode virtuelle pure : toute classe dérivée doit obligatoirement la redéfinir.*/
    virtual bool intersect(const Ray& ray, double& t) const = 0;
    virtual Vec3 getNormal(const Vec3& p) const = 0;
    virtual ~Object3D() = default;
};
