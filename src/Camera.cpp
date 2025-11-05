#define _USE_MATH_DEFINES
#include "Camera.h"
#include "Constants.h"
#include <cmath>

Camera::Camera(const Vec3& pos, const Vec3& lookAt, double fovDeg) {
    position = pos;

    // Conversion du FOV de degrés en radians
    fov = fovDeg * M_PI / 180.0;

    // Calcul des axes de la caméra
    forward = (lookAt - pos).normalized();// vecteur pointant de la caméra vers le point visé (lookAt).
    right   = Vec3::cross(forward, Vec3(0, 1, 0)).normalized();// vecteur perpendiculaire à forward et au vecteur vertical (0,1,0) du monde (produit vectoriel).
    up      = Vec3::cross(right, forward).normalized(); // vecteur perpendiculaire à forward et right pour compléter le repère orthonormé.
}

Ray Camera::generateRay(int x, int y, int width, int height) const {
    double aspect = static_cast<double>(width) / height;

    // Coordonnées normalisées du pixel
    double px = (2 * ((x + 0.5) / static_cast<double>(width)) - 1) * tan(fov / 2) * aspect;
    double py = (1 - 2 * ((y + 0.5) / static_cast<double>(height))) * tan(fov / 2);

    // Direction finale du rayon
    Vec3 dir = (forward + right * px + up * py).normalized();

    return Ray(position, dir);
}
