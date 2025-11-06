#pragma once
#include <cmath>
#include <algorithm>

struct Vec3 {
    double x, y, z;

    Vec3(double value = 0.0) : x(value), y(value), z(value) {}
    Vec3(double xValue, double yValue, double zValue) : x(xValue), y(yValue), z(zValue) {}

    Vec3 operator+(const Vec3& other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vec3 operator-(const Vec3& other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vec3 operator*(double scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    Vec3 operator/(double scalar) const { return {x / scalar, y / scalar, z / scalar}; }

    Vec3 operator-() const { return {-x, -y, -z}; }

    Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    Vec3& operator*=(double scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Vec3& operator/=(double scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    friend Vec3 operator*(double scalar, const Vec3& vector) {
        return {vector.x * scalar, vector.y * scalar, vector.z * scalar};
    }
};

// Mesur l'angle entre deux vecteurs
inline double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
// Norme (longueur) d'un vecteur
inline double length(const Vec3& vector) {
    return std::sqrt(dot(vector, vector));
}
// Retourne un vecteur normalisé (même direction, longueur = 1)
inline Vec3 normalize(const Vec3& v) {
    double L = length(v);
    return (L > 0.0) ? v / L : v;
}
// Calcule la direction du rayon réfléchi
inline Vec3 reflect(const Vec3& incident, const Vec3& normal) {
    return incident - normal * (2.0 * dot(incident, normal));
}

inline Vec3 clamp01(const Vec3& c) {
    auto clamp = [](double value) { return std::max(0.0, std::min(1.0, value)); };
    return {clamp(c.x), clamp(c.y), clamp(c.z)};
}