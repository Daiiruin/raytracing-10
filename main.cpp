#include "scene/SceneLoader.hpp"
#include "render/Renderer.hpp"

int main(){
    Scene scene=loadScene("scene.json");
    Renderer renderer;
    renderer.maxDepth=3;
    renderer.render(scene);
    return 0;
}
