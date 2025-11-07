#include "scene/SceneLoader.hpp"
#include "renderer/Renderer.hpp"

int main() {
    try {
        Scene scene = loadScene("scene.json");
        std::cout << "Scène chargée avec succès." << std::endl;

        Renderer renderer;
        renderer.maxDepth = 3;

        std::cout << "Démarrage du rendu..." << std::endl;
        renderer.render(scene);

        std::cout << "Rendu terminé avec succès !" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
