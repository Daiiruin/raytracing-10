#include "scene/SceneLoader.hpp"
#include "renderer/Renderer.hpp"
#include <chrono>


int main() {
     
    try {
        // --- Mesure du temps de rendu
    auto start = std::chrono::high_resolution_clock::now();
        Scene scene = loadScene("scene.json");
        std::cout << "Scène chargée avec succès." << std::endl;

        Renderer renderer;
        renderer.maxDepth = 3;

        std::cout << "Démarrage du rendu..." << std::endl;
        renderer.render(scene);

        std::cout << "Rendu terminé avec succès !" << std::endl;
        // --- Fin du rendu
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
 

    std::cout << "Rendu terminé en " << elapsed.count() << " secondes.\n";
    return 0;
}
