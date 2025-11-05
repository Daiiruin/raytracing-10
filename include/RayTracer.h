#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Vec3.h"       // Vecteur 3D pour position, couleur, direction, etc.
#include "Ray.h"        // Classe Ray pour représenter un rayon
#include "Scene.h"      // Contient tous les objets et leur intersection
#include "Camera.h"     // Classe Camera pour générer les rayons
#include <string>       // Pour utiliser std::string
#include <vector>       // Pour stocker les pixels en PNG

class RayTracer {
public:
    // --- Constructeur ---
    RayTracer();  

    // --- Trace un rayon et retourne la couleur correspondante
    // depth = profondeur de récursion pour les réflexions
    Vec3 trace(const Ray& ray, int depth = 0) const;

    // --- Tableau de pixels (R,G,B) pour générer un PNG
    std::vector<unsigned char> pixels;

    // --- Rend la scène entière depuis la caméra
    // width, height : dimensions de l'image
    // filename : nom du fichier PPM de sortie
    void render(const Camera& cam, int width, int height, const std::string& filename);

    // --- Permet de définir la scène depuis l'extérieur
    void setScene(const Scene& s) { scene = s; }

    // --- Membres publics principaux
    Scene scene;       // La scène contenant tous les objets
    Vec3 lightDir;     // Direction de la lumière principale
};

#endif // RAYTRACER_H
