#pragma once
#include <random>
#include "math.hpp"

namespace rt {

inline Vec3 sampleInCone(const Vec3& dir, double cosThetaMax, double u1, double u2) {
    Vec3 w = normalize(dir);
    Vec3 a = (std::fabs(w.x) > 0.1) ? Vec3{0,1,0} : Vec3{1,0,0};
    Vec3 v = normalize(cross(w, a));
    Vec3 u = cross(v, w);

    double cosTheta = (1.0 - u1) + u1 * cosThetaMax;
    double sinTheta = std::sqrt(std::max(0.0, 1.0 - cosTheta*cosTheta));
    double phi = 2.0 * PI * u2;

    return normalize( u*(std::cos(phi)*sinTheta) + v*(std::sin(phi)*sinTheta) + w*cosTheta );
}

template <class RNG>
inline double softShadowVisibility(const Vec3& p, const Vec3& Ldir,
                                   double cone_angle_deg, int samples,
                                   const auto& intersectFn, RNG& rng)
{
    if (samples <= 1) {
        return intersectFn(p, Ldir) ? 0.0 : 1.0;
    }
    std::uniform_real_distribution<double> U(0.0, 1.0);
    double theta = cone_angle_deg * PI / 180.0;
    double cosThetaMax = std::cos(theta);

    int unoccluded = 0;
    for (int i=0;i<samples;++i) {
        Vec3 d = sampleInCone(Ldir, cosThetaMax, U(rng), U(rng));
        if (!intersectFn(p, d)) unoccluded++;
    }
    return double(unoccluded) / double(samples);
}

}
