#pragma once
#include "Object.hpp"

struct Sphere : Object {
    Vec3 center;
    double radius;

    Sphere(const Vec3& centerPosition, double sphereRadius, const Material& materialInput) {
        center = centerPosition;
        radius = sphereRadius;
        material = materialInput;
    }

    // Teste l'intersection entre un rayon et la sphère
    std::optional<HitRecord> intersect(const Ray& ray, double minDistance, double maxDistance) const override {
        // Vecteur entre l'origine du rayon et le centre de la sphère
        Vec3 originToCenter = ray.origin - center;

        // Coefficients de l'équation quadratique : a*t² + b*t + c = 0
        double a = dot(ray.direction, ray.direction);
        double b = 2.0 * dot(originToCenter, ray.direction);
        double c = dot(originToCenter, originToCenter) - radius * radius; 
        
        // Discriminant : détermine s'il y a une intersection
        double discriminant = b * b - 4.0 * a * c;
        if (discriminant < 0.0) return std::nullopt;

        double sqrtDiscriminant = std::sqrt(discriminant);

        // On teste les deux racines (entrée et sortie du rayon dans la sphère)
        double t = (-b - sqrtDiscriminant) / (2.0 * a);
        if (t < minDistance || t > maxDistance) {
            t = (-b + sqrtDiscriminant) / (2.0 * a);
            if (t < minDistance || t > maxDistance)
                return std::nullopt;
        }
        
        // Calcul du point d'impact et de la normale
        Vec3 impactPoint = ray.origin + ray.direction * t;
        Vec3 normalAtImpact = normalize(impactPoint - center);

        // Création du résultat
        HitRecord hit;
        hit.distanceFromRayOrigin = t;
        hit.impactPoint = impactPoint;
        hit.surfaceNormal = normalAtImpact;
        hit.material = &material;

        return hit;
    }
};
