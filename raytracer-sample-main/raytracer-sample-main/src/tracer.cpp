#include "rt/tracer.hpp"
#include "rt/math.hpp"

namespace rt {

Vec3 sky(const Ray& r) {
    double t = 0.5*(normalize(r.d).y + 1.0);
    Vec3 top = {0,0,0};
    Vec3 bot = {0.02,0.02,0.03};
    return bot*(1.0-t) + top*t;
}

template <class RNG>
Vec3 shade(const Ray& r, const Hit& h, const Material& mat,
           const Scene& sc, const LightDir& L, RNG& rng)
{
    // closure d'intersection pour soft shadows
    auto shadowIntersect = [&](const Vec3& p, const Vec3& d)->bool{
        Ray sray{ p + d * (-EPS), d };
        Hit hh; Material mm;
        return intersectScene(sray, sc, hh, mm);
    };

    double vis = softShadowVisibility(h.p + h.n*EPS, L.dir,
                                      L.cone_angle_deg, L.shadow_samples,
                                      shadowIntersect, rng);

    double nl = std::max(0.0, dot(h.n, L.dir));
    Vec3 diffuse = mat.color * (L.ambient + vis * 0.95 * nl);

    Vec3 V = normalize(r.o - h.p);
    Vec3 H = normalize(L.dir + V);
    double spec = vis * std::pow(std::max(0.0, dot(h.n, H)), L.shininess) * L.specStrength;

    return clamp01(diffuse + Vec3{spec,spec,spec});
}

template <class RNG>
Vec3 trace(const Ray& r, const Scene& sc, const LightDir& L, RNG& rng, int depth) {
    Hit h; Material mat;
    if (!intersectScene(r, sc, h, mat)) {
        return sky(r);
    }

    Vec3 local = shade(r, h, mat, sc, L, rng);

    if (depth < 2 && mat.reflectivity > 0.0) {
        Vec3 R = normalize(r.d - h.n * (2.0 * dot(r.d, h.n)));
        Ray rr{ h.p + h.n*EPS, R };
        Vec3 refl = trace(rr, sc, L, rng, depth+1);
        local = local*(1.0 - mat.reflectivity) + refl*mat.reflectivity;
    }
    return local;
}

// ---- explicit instantiations (pour éviter les templates uniquement-headers)
template Vec3 shade<std::mt19937>(const Ray&, const Hit&, const Material&,
                                  const Scene&, const LightDir&, std::mt19937&);
template Vec3 trace<std::mt19937>(const Ray&, const Scene&, const LightDir&,
                                  std::mt19937&, int);

} // namespace rt
