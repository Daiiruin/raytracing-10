#pragma once
#include "Vec3.hpp"
#include "Material.hpp"
//structure clé du moteur de rendu
struct HitRecord {
    double distanceFromRayOrigin; // Distance entre l'origine du rayon et le point d'impact
    Vec3 impactPoint; // Coordonnées exactes du point d'impact dans la scène
    Vec3 surfaceNormal; // Normale de la surface au point d'impact
    const Material* material; // Matériau de l'objet touché
};
