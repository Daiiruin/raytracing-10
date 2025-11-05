#include <random>
#include <iostream>

#include "Color.hpp"
#include "Image.hpp"

#include "rt/camera.hpp"
#include "rt/tracer.hpp"
#include "rt/scene.hpp"
#include "rt/light.hpp"
#include "rt/math.hpp"

int main() {
    using namespace rt;

    const int W = 1600, H = 900;
    Image img(W, H, Color(0,0,0));

    Camera cam;
    LightDir light;                 // ombres douces activées (cone_angle_deg / samples)

    // scène : sphère et damier, avec réflexions
    Scene scene;
    scene.sphere = Sphere{ {0.0, 1.0, 5.0}, 1.0, {0.15, 0.75, 0.95} };
    scene.tile = 0.9;
    scene.colA = {0.92,0.92,0.92};
    scene.colB = {0.08,0.08,0.08};
    scene.reflectivity_plane  = 0.4;   // miroir partiel
    scene.reflectivity_sphere = 0.15;  // léger reflet

    // AA 4×4 jittered
    const int spp_side = 4;
    const double inv_spp = 1.0 / (spp_side*spp_side);
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> U(0.0, 1.0);

    for (int y = 0; y < H; ++y) {
        int iy = H - 1 - y;
        for (int x = 0; x < W; ++x) {
            Vec3 c{0,0,0};
            for (int sy = 0; sy < spp_side; ++sy)
            for (int sx = 0; sx < spp_side; ++sx) {
                double jx = (sx + U(rng)) / spp_side;
                double jy = (sy + U(rng)) / spp_side;
                double u = x + jx;
                double v = iy + jy;
                Ray ray = cam.getWorldRay(u, v, W, H);
                c = c + trace(ray, scene, light, rng);
            }  
            c = clamp01(c * inv_spp);
            // gamma 2.2
            c = { std::pow(c.x, 1.0/2.2), std::pow(c.y, 1.0/2.2), std::pow(c.z, 1.0/2.2) };
            img.SetPixel(x, y, Color(c.x, c.y, c.z));
        }
    }

    img.WriteFile("../output.png"); 
    std::cout << "✅ output.png générée\n";
    return 0;
}
