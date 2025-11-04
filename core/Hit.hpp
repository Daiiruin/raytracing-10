#pragma once
#include "Vec3.hpp"
#include "Material.hpp"

struct Hit {
    double t; // Distance origine rayon -> point d'impact
    Vec3 p; // Point d'impact
    Vec3 n; // Normale au point d'impact
    const Material* mat; // Matériau de lobjet impacté
};
