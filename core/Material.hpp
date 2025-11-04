#pragma once
#include "Vec3.hpp"

struct Material {
    Vec3 color{1,1,1}; // Coueleur de la surface
    double diffuse=0.7; // Rendu mat
    double specular=0.5; // Intensité du reflet
    double shininess=32.0; // Taille du reflet
    double reflectivity=0.0; // Pourcentage de réflexion
};
