#pragma once
#include "Vec3.hpp"

struct Material {
    Vec3 baseColor {1.0, 1.0, 1.0}; // Couleur de base de la surface (RGB)
    double diffuseFactor = 0.7; // Composante diffuse : proportion de lumière diffusée (aspect mat)
    double specularFactor = 0.5; // Composante spéculaire : intensité des reflets brillants
    double shininess = 32.0; // Contrôle la taille / netteté du reflet (plus élevé = reflet concentré)
    double reflectivity = 0.0; // Taux de réflexion du matériau (0 = mat, 1 = miroir parfait)
};