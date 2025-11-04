#pragma once
#include <cmath>
#include <algorithm>

struct Vec3 {
    double x, y, z;

    Vec3(double v = 0) : x(v), y(v), z(v) {}
    Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator*(double s) const { return {x * s, y * s, z * s}; }
    Vec3 operator/(double s) const { return {x / s, y / s, z / s}; }

    Vec3 operator-() const { return {-x, -y, -z}; }

    Vec3& operator+=(const Vec3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vec3& operator-=(const Vec3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    Vec3& operator*=(double s) { x *= s; y *= s; z *= s; return *this; }
    Vec3& operator/=(double s) { x /= s; y /= s; z /= s; return *this; }

    friend Vec3 operator*(double s, const Vec3& v) {
        return {v.x * s, v.y * s, v.z * s};
    }
};

// Produit scalaire
// Mesur l'angle entre deux vecteurs
inline double dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
// Calcul la norme (longueur) d'un vecteur
inline double length(const Vec3& v) { return std::sqrt(dot(v, v)); }
// Renvoi d'un vecteur (longueur = 1)
inline Vec3 normalize(const Vec3& v) { double L = length(v); return (L > 0) ? v / L : v; }
inline Vec3 reflect(const Vec3& I, const Vec3& N) { return I - N * (2.0 * dot(I, N)); }

inline Vec3 clamp01(const Vec3& c) {
    auto cl = [](double v) { return std::max(0.0, std::min(1.0, v)); };
    return {cl(c.x), cl(c.y), cl(c.z)};
}
