#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Renderer.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include "../core/Utils.hpp"
#include <stb/stb_image_write.h>

static bool nearestHit(const Scene& scene,const Ray& r,double tMin,double tMax,Hit& out){
    bool hit=false; double closest=tMax;
    for(const auto& obj: scene.objects){
        auto h=obj->intersect(r,tMin,closest);
        if(h){ hit=true; closest=h->t; out=*h; }
    }
    return hit;
}

static Vec3 shade(const Scene& scene,const Ray& r,int depth){
    if(depth<=0) return {0,0,0};
    Hit h; if(!nearestHit(scene,r,1e-4,1e9,h)) return {0,0,0};
    Vec3 color= h.mat->color * scene.ambient.x; // simple ambient
    Vec3 V=normalize(-r.d);
    for(auto& L: scene.lights){
        Vec3 Ldir=normalize(L.pos-h.p);
        double NdotL=std::max(0.0,dot(h.n,Ldir));
        Vec3 diff=h.mat->color * (h.mat->diffuse*NdotL);
        Vec3 H=normalize(Ldir+V);
        double NdotH=std::max(0.0,dot(h.n,H));
        Vec3 spec=L.intensity*(h.mat->specular*pow(NdotH,h.mat->shininess));
        color=color+diff+spec;
    }
    return clamp01(color);
}

void Renderer::render(const Scene& scene){
    double aspect=(double)scene.width/scene.height;
    double fov=scene.fov*M_PI/180.0; double scale=tan(fov*0.5);
    Vec3 forward=normalize(scene.camLook-scene.camPos);
    Vec3 right=normalize(Vec3(forward.y*scene.camUp.z-forward.z*scene.camUp.y,
                              forward.z*scene.camUp.x-forward.x*scene.camUp.z,
                              forward.x*scene.camUp.y-forward.y*scene.camUp.x));
    Vec3 up=normalize(Vec3(right.y*forward.z-right.z*forward.y,
                           right.z*forward.x-right.x*forward.z,
                           right.x*forward.y-right.y*forward.x));

    std::vector<Vec3> framebuffer(scene.width*scene.height);
    for(int y=0;y<scene.height;y++){
        for(int x=0;x<scene.width;x++){
            double ndc_x=((x+0.5)/scene.width)*2-1;
            double ndc_y=((y+0.5)/scene.height)*2-1;
            ndc_x*=aspect*scale; ndc_y*=-scale;
            Vec3 dir=normalize(forward+right*ndc_x+up*ndc_y);
            Ray r{scene.camPos,dir};
            framebuffer[y*scene.width+x]=shade(scene,r,maxDepth);
        }
        if(y%20==0) std::cerr<<"Ligne "<<y<<"/"<<scene.height<<"\n";
    }
    // Conversion du framebuffer en tableau d'octets (RGB 8 bits)
    std::vector<unsigned char> pixels(scene.width * scene.height * 3);

    for (int y = 0; y < scene.height; ++y) {
        for (int x = 0; x < scene.width; ++x) {
            Vec3 c = clamp01(framebuffer[y * scene.width + x]);
            int idx = (y * scene.width + x) * 3;
            pixels[idx + 0] = static_cast<unsigned char>(255 * c.x);
            pixels[idx + 1] = static_cast<unsigned char>(255 * c.y);
            pixels[idx + 2] = static_cast<unsigned char>(255 * c.z);
        }
    }

    std::string pngOutput = scene.output;
    if (pngOutput.size() >= 4 && pngOutput.substr(pngOutput.size() - 4) == ".ppm")
        pngOutput = pngOutput.substr(0, pngOutput.size() - 4) + ".png";

    if (stbi_write_png(pngOutput.c_str(), scene.width, scene.height, 3,
                    pixels.data(), scene.width * 3)) {
        std::cerr << "OK -> " << pngOutput << "\n";
    } else {
        std::cerr << "Erreur lors de l'écriture du PNG\n";
    }
}