#pragma once
#include "Object.hpp"

struct Plane : Object {
    Vec3 normal;
    double distanceFromOrigin;

    Plane(const Vec3& normalVector, double distance, const Material& materialInput) {
        normal = normalize(normalVector);
        distanceFromOrigin = distance;
        material = materialInput;
    }

    // Teste l'intersection entre un rayon et le plan
    std::optional<HitRecord> intersect(const Ray& ray, double minDistance, double maxDistance) const override {
        // Produit scalaire entre la normale du plan et la direction du rayon
        double denominator = dot(normal, ray.direction);
        
        // Si le rayon est parallèle au plan, pas d'intersection
        if (std::fabs(denominator) < 1e-6) return std::nullopt;
        
        // Calcul de la distance t depuis l'origine du rayon jusqu'au point d'impact
        double t = -(dot(normal, ray.origin) + distanceFromOrigin) / denominator;
        
        // Si l'intersection est en dehors de la plage souhaitée, on ignore
        if (t < minDistance || t > maxDistance) return std::nullopt;

        // Création du point d'impact et enregistrement de la collision
        HitRecord hit;
        hit.distanceFromRayOrigin = t;
        hit.impactPoint = ray.origin + ray.direction * t;
        hit.surfaceNormal = normal;
        hit.material = &material;

        return hit;
    }
};