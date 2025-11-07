#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../core/Vec3.hpp"
#include "../objects/Object.hpp"

struct PointLight { // source de lumiere dans la scene
    Vec3 position, intensity; //l'intensité de la lumiere , utiliser pour coder la couleur et la puissance de la lumiere en format RGB
};

struct Scene {
    int width = 500;
    int height = 400;
    std::string output = "output.png";

    Vec3 cameraPosition { 0.0, 0.0, 0.0 };
    Vec3 cameraTarget { 0.0, 0.0, -1.0 };  //direction de la camera
    Vec3 cameraUp { 0.0, 1.0, 0.0 };       // haut de la camera pour définir l'orientation
    double fov  = 45.0;                    // champs de vision 

    Vec3 ambientLightIntensity { 0.1, 0.1, 0.1 };// lumiere ambiante pour eviter les zones noire

    std::vector<PointLight> lights; // lampes presentes dans la scene 
    std::vector<std::unique_ptr<Object>> objects; // objects 3D dans la scene, stockés dans un pointeur
};
// cette classe sert à définir tout les composants d'une scene 3D
//parametres de la caméra
//lumieres
//objets
//la taille de l'image de sortie
//utilisé par un moteur de rendu pour générer une image