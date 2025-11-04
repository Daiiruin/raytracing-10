#pragma once
#include "Scene.hpp"
#include "../core/Material.hpp"
#include "../objects/Sphere.hpp"
#include "../objects/Plane.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

inline Vec3 parseVec3(const json& j,const std::string& x="x",const std::string& y="y",const std::string& z="z"){
    return { j.value(x,0.0), j.value(y,0.0), j.value(z,0.0) };
}
inline Vec3 parseColor(const json& j){ return { j.value("r",0.0), j.value("g",0.0), j.value("b",0.0) }; }

inline Material parseMaterial(const json& j){
    Material m;
    m.color=parseColor(j["color"]);
    m.diffuse=j.value("diffuse",0.7);
    m.specular=j.value("specular",0.5);
    m.shininess=j.value("shininess",32.0);
    m.reflectivity=j.value("reflectivity",0.0);
    return m;
}

inline Scene loadScene(const std::string& path){
    std::ifstream f(path); json j; f>>j;
    Scene s;
    // config
    s.width=j["config"].value("width",500);
    s.height=j["config"].value("height",400);
    s.output=j["config"].value("output_file","output.ppm");
    // camera
    s.camPos=parseVec3(j["camera"]["position"]);
    s.camLook=parseVec3(j["camera"]["lookAt"]);
    s.camUp=parseVec3(j["camera"]["up"]);
    s.fov=j["camera"].value("fov",45.0);
    // ambient
    s.ambient=parseColor(j["scene"]["ambient_light"]);
    // lights
    for(auto& lj: j["scene"]["lights"])
        s.lights.push_back({parseVec3(lj["position"]), parseColor(lj["intensity"])});
    // objects
    for(auto& oj: j["scene"]["objects"]){
        std::string type=oj.value("type","");
        Material m=parseMaterial(oj["material"]);
        if(type=="sphere") s.objects.push_back(std::make_unique<Sphere>(parseVec3(oj["center"]), oj.value("radius",1.0), m));
        else if(type=="plane") s.objects.push_back(std::make_unique<Plane>(parseVec3(oj["normal"]), oj.value("distance",0.0), m));
    }
    return s;
}
