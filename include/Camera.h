#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "Constants.h"

class Camera {
public:
    Vec3 position; // Position de la caméra dans le monde 3D
    Vec3 forward;  // Direction dans laquelle la caméra regarde
    Vec3 right;    // Vecteur "droit" de la caméra, perpendiculaire à forward et up
    Vec3 up;       // Vecteur "haut" de la caméra, pour l’orientation verticale
    double fov;    // Champ de vision en degrés (Field of View)

    Camera(const Vec3& pos, const Vec3& lookAt, double fovDeg);
    /* pos → position dans le monde.
     lookAt → point que la caméra doit viser.
     fovDeg → angle de champ de vision en degrés.*/
    Ray generateRay(int x, int y, int width, int height) const;
    /*Cette fonction retourne un rayon 3D passant par le pixel (x, y) de l’écran.
    (x, y) → coordonnées du pixel à l’écran.
     width, height) → dimensions de l’écran ou de l’image.
     C’est cette fonction qui permet de lancer des rayons depuis la caméra pour le ray tracing.*/
};
