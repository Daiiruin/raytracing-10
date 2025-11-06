#pragma once
#include "Scene.hpp"
#include "../core/Material.hpp"
#include "../objects/Sphere.hpp"
#include "../objects/Plane.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

// Convertit un objet JSON en Vec3 (avec clés x, y, z)
inline Vec3 parseVec3(const json& j, const std::string& keyX = "x", const std::string& keyY = "y", const std::string& keyZ = "z") {
    return { j.value(keyX, 0.0), j.value(keyY, 0.0), j.value(keyZ, 0.0) };
}
// Convertit un objet JSON en couleur RGB (avec clés r, g, b)
inline Vec3 parseColor(const json& j) {
    return { j.value("r", 0.0), j.value("g", 0.0), j.value("b", 0.0) };
}

// Convertit un objet JSON en matériau
inline Material parseMaterial(const json& materialJson) {
    Material material;
    material.baseColor = parseColor(materialJson["color"]);
    material.diffuseFactor = materialJson.at("diffuse");
    material.specularFactor = materialJson.at("specular");
    material.shininess = materialJson.at("shininess");
    material.reflectivity = materialJson.at("reflectivity");
    return material;
}

inline Scene loadScene(const std::string& jsonFilePath){
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Fichier JSON non trouvé");
    }

    json jsonData;
    file >> jsonData;
    Scene scene;

    // Configuration générale
    const auto& config = jsonData["config"];
    scene.width = config.at("width");
    scene.height = config.at("height");
    scene.output = config.at("output_file");

    // Caméra
    const auto& camera = jsonData["camera"];
    scene.cameraPosition = parseVec3(camera["position"]);
    scene.cameraTarget = parseVec3(camera["lookAt"]);
    scene.cameraUp = parseVec3(camera["up"]);
    scene.fov = camera.at("fov");

    // Lumière ambiante
    scene.ambientLightIntensity = parseColor(jsonData["scene"]["ambient_light"]);

    // Lumières ponctuelles
    for (const auto& lightJson : jsonData["scene"]["lights"]) {
        PointLight light;
        light.position  = parseVec3(lightJson["position"]);
        light.intensity = parseColor(lightJson["intensity"]);
        scene.lights.push_back(light);
    }

    // objects
    for (const auto& objectJson : jsonData["scene"]["objects"]) {
        std::string objectType = objectJson.value("type", "");
        Material material = parseMaterial(objectJson["material"]);

        if (objectType == "sphere") {
            Vec3 center = parseVec3(objectJson["center"]);
            double radius = objectJson.at("radius");
            scene.objects.push_back(std::make_unique<Sphere>(center, radius, material));
        }
        else if (objectType == "plane") {
            Vec3 normal = parseVec3(objectJson["normal"]);
            double distance = objectJson.at("distance");
            scene.objects.push_back(std::make_unique<Plane>(normal, distance, material));
        }
        else {
            std::cerr << "Type d'objet inconnu : " << objectType << std::endl;
        }
    }

    return scene;
}
