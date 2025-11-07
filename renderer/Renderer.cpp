#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Renderer.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <numbers>
#include <stb/stb_image_write.h>

// Trouve la première intersection entre un rayon et les objets de la scène
static bool findNearestIntersection(const Scene& scene,const Ray& ray,double minDistance,double maxDistance,HitRecord& outHit){
    bool hasHit = false;
    double closestDistance = maxDistance;

    for (const auto& object : scene.objects) {
        auto hit = object->intersect(ray, minDistance, closestDistance);
        if (hit) {
            hasHit = true;
            closestDistance = hit->distanceFromRayOrigin;
            outHit = *hit;
        }
    }
    return hasHit;
}

// Vérifie si un point est dans l'ombre par rapport à une lumière donnée
static bool isInShadow(const Scene& scene,const Vec3& point,const Vec3& lightPosition){
    Vec3 toLight = lightPosition - point;
    double lightDistance = std::sqrt(dot(toLight, toLight));
    Vec3 lightDirection = toLight / lightDistance;

    Ray shadowRay { point + lightDirection * 1e-4, lightDirection };
    HitRecord tempHit;

    return findNearestIntersection(scene, shadowRay, 1e-4, lightDistance - 1e-4, tempHit);
}

// Calcule la couleur d'un rayon en prenant en compte la lumière et les reflets
static Vec3 shade(const Scene& scene, const Ray& ray, int depth) {
    if (depth <= 0) return {0, 0, 0};

    HitRecord hit;
    if (!findNearestIntersection(scene, ray, 1e-4, 1e9, hit))
        return {0, 0, 0}; // aucun objet touché → noir
    
    // Couleur de base = lumière ambiante
    Vec3 color = {
        hit.material->baseColor.x * scene.ambientLightIntensity.x,
        hit.material->baseColor.y * scene.ambientLightIntensity.y,
        hit.material->baseColor.z * scene.ambientLightIntensity.z
    };

    // Vecteur vers la caméra
    Vec3 viewDirection = normalize(-ray.direction);

    // Pour chaque lumière dans la scène
    for (const auto& light : scene.lights) {
        if (isInShadow(scene, hit.impactPoint, light.position))
            continue;

        Vec3 lightDirection = normalize(light.position - hit.impactPoint);
        double NdotL = std::max(0.0, dot(hit.surfaceNormal, lightDirection));

        // Composante diffuse (rendu mat)
        Vec3 diffuse = hit.material->baseColor * (hit.material->diffuseFactor * NdotL);

        // Composante spéculaire (reflet brillant)
        Vec3 halfway = normalize(lightDirection + viewDirection);
        double NdotH = std::max(0.0, dot(hit.surfaceNormal, halfway));
        Vec3 specular = light.intensity * (hit.material->specularFactor * pow(NdotH, hit.material->shininess));

        // Ajout à la couleur finale
        color += diffuse + specular;
    }

    // Réflexion (si le matériau est réfléchissant)
    if (hit.material->reflectivity > 0.0) {
        Vec3 reflectedDir = reflect(ray.direction, hit.surfaceNormal);
        Ray reflectedRay { hit.impactPoint + reflectedDir * 1e-4, normalize(reflectedDir) };
        Vec3 reflectedColor = shade(scene, reflectedRay, depth - 1);
        color = (1 - hit.material->reflectivity) * color + hit.material->reflectivity * reflectedColor;
    }

    return clamp01(color);
}

// Fonction principale de rendu : génère l'image pixel par pixel
void Renderer::render(const Scene& scene){
    double aspectRatio = static_cast<double>(scene.width) / scene.height;
    double fovRadians = scene.fov * std::numbers::pi / 180.0;
    double scale = tan(fovRadians * 0.5);

    // Vecteurs de base de la caméra (forward, right, up)
    Vec3 forward = normalize(scene.cameraTarget - scene.cameraPosition);

    Vec3 right = normalize(Vec3(
        forward.y * scene.cameraUp.z - forward.z * scene.cameraUp.y,
        forward.z * scene.cameraUp.x - forward.x * scene.cameraUp.z,
        forward.x * scene.cameraUp.y - forward.y * scene.cameraUp.x
    ));

    Vec3 up = normalize(Vec3(
        right.y * forward.z - right.z * forward.y,
        right.z * forward.x - right.x * forward.z,
        right.x * forward.y - right.y * forward.x
    ));

    // Framebuffer pour stocker la couleur de chaque pixel
    std::vector<Vec3> framebuffer(scene.width * scene.height);

    for (int y = 0; y < scene.height; ++y) {
        for (int x = 0; x < scene.width; ++x) {
            // Coordonnées normalisées (de -1 à 1)
            double ndcX = ((x + 0.5) / scene.width) * 2 - 1;
            double ndcY = ((y + 0.5) / scene.height) * 2 - 1;
            ndcX *= aspectRatio * scale;
            ndcY *= -scale;

            // Direction du rayon pour ce pixel
            Vec3 rayDirection = normalize(forward + right * ndcX + up * ndcY);
            Ray ray { scene.cameraPosition, rayDirection };

            // Calcul de la couleur via ray tracing
            framebuffer[y * scene.width + x] = shade(scene, ray, maxDepth);
        }

        if (y % 20 == 0)
            std::cerr << "Ligne " << y << "/" << scene.height << "\n";
    }


    // Conversion du framebuffer en pixels 8 bits
    std::vector<unsigned char> pixels(scene.width * scene.height * 3);
    for (int y = 0; y < scene.height; ++y) {
        for (int x = 0; x < scene.width; ++x) {
            Vec3 c = clamp01(framebuffer[y * scene.width + x]);
            int index = (y * scene.width + x) * 3;
            pixels[index + 0] = static_cast<unsigned char>(255 * c.x);
            pixels[index + 1] = static_cast<unsigned char>(255 * c.y);
            pixels[index + 2] = static_cast<unsigned char>(255 * c.z);
        }
    }

    // Sortie de l'image finale en PNG
    std::string outputFile = scene.output;
    if (outputFile.size() >= 4 && outputFile.substr(outputFile.size() - 4) == ".ppm")
        outputFile = outputFile.substr(0, outputFile.size() - 4) + ".png";

    if (stbi_write_png(outputFile.c_str(), scene.width, scene.height, 3, pixels.data(), scene.width * 3)) {
        std::cerr << "Rendu terminé : " << outputFile << "\n";
    } else {
        std::cerr << "Erreur lors de l'écriture du fichier PNG\n";
    }
}