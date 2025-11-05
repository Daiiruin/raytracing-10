#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "RayTracer.h"
#include <fstream>
#include <algorithm>
#include <string> 

// --- Constructeur ---
RayTracer::RayTracer() : lightDir(Vec3(1,1,-1).normalized()) {}

// --- Fonction de trace de rayon ---
Vec3 RayTracer::trace(const Ray& ray, int depth) const {
    if (depth > 3) return Vec3(0,0,0);

    Vec3 hitPoint, normal;
    Material mat;
    if (!scene.intersect(ray, hitPoint, normal, mat))
        return Vec3(0,0,0);

    double diff = std::max(0.0, normal.dot(lightDir));
    Vec3 localColor = mat.color * diff;

    if (mat.reflectivity > 0) {
        Vec3 reflDir = ray.direction - normal * 2 * ray.direction.dot(normal);
        Ray reflRay(hitPoint + reflDir * 1e-4, reflDir);
        Vec3 reflColor = trace(reflRay, depth+1);
        localColor = localColor*(1-mat.reflectivity) + reflColor*mat.reflectivity;
    }

    return localColor;
}

// --- Fonction de rendu PPM + stockage pixels pour PNG ---
void RayTracer::render(const Camera& cam, int width, int height, const std::string& filename) {
    // Redimensionne le tableau pixels pour PNG
    pixels.resize(width * height * 3);

    std::ofstream out(filename);
    out << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Ray ray = cam.generateRay(x, y, width, height);
            Vec3 color = trace(ray);

            int r = std::min(255, (int)(255*color.x));
            int g = std::min(255, (int)(255*color.y));
            int b = std::min(255, (int)(255*color.z));

            // Écrire dans le PPM
            out << r << " " << g << " " << b << "\n";

            // Stocker dans pixels pour PNG
            int i = (y * width + x) * 3;
            pixels[i+0] = (unsigned char)r;
            pixels[i+1] = (unsigned char)g;
            pixels[i+2] = (unsigned char)b;
        }
    }

    out.close();

    // --- Génération PNG ---
    //stbi_flip_vertically_on_write(1); // faire correspondre l'orientation du PNG au PPM
    stbi_write_png("output/output.png", width, height, 3, pixels.data(), width*3);
}
