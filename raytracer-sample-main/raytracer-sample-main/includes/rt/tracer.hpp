#pragma once
#include <random>
#include "ray.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "sampling.hpp"

namespace rt {

Vec3 sky(const Ray& r);
template <class RNG>
Vec3 shade(const Ray& r, const Hit& h, const Material& mat,
           const Scene& sc, const LightDir& L, RNG& rng);

template <class RNG>
Vec3 trace(const Ray& r, const Scene& sc, const LightDir& L, RNG& rng, int depth=0);

}
