#include <iostream>
#include <chrono>
#include "Scene.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Material.h"

int main() {
    // --- Mesure du temps de rendu
    auto start = std::chrono::high_resolution_clock::now();

    // --- Création du RayTracer
    RayTracer rt;

    // --- Création de la scène
    rt.scene.add(new Sphere(Vec3(0,0,-5), 1, Material(Vec3(0.9,0.9,0.9), 0.5)));
    rt.scene.add(new Sphere(Vec3(-2,0,-5), 1, Material(Vec3(0.8,0.1,0.1), 0.2)));
    rt.scene.add(new Sphere(Vec3(2,0,-5), 1, Material(Vec3(0.1,0.1,0.8), 0.2)));
    rt.scene.add(new Plane(Vec3(0,1,0), 1, Material(Vec3(0.3,0.3,0.3), 0.5)));

    // --- Création de la caméra
    Camera cam(Vec3(0,0,0), Vec3(0,0,-1), 60);

    // --- Dimensions de l'image
    int width = 800;
    int height = 600;

    // --- Fichier PPM de sortie
    std::string ppmFile = "output/output.ppm";

    // --- Lancer le rendu (remplit rt.pixels et écrit le PPM + PNG)
    rt.render(cam, width, height, ppmFile);

    // --- Fin du rendu
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Rendu terminé en " << elapsed.count() << " secondes.\n";
    std::cout << "Fichiers générés : " << ppmFile << " et output/output.png\n";

    return 0;
}
