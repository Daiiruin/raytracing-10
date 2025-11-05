#pragma once
#include <cmath>

struct Vec3 {
    double x, y, z;
    Vec3(double x_=0, double y_=0, double z_=0): x(x_), y(y_), z(z_) {}

    Vec3 operator+(const Vec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    Vec3 operator*(double s) const { return {x*s, y*s, z*s}; }
    Vec3 operator/(double s) const { return {x/s, y/s, z/s}; }

    double dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
    Vec3 cross(const Vec3& v) const {
        return {y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x};
    }

    double length() const { return std::sqrt(x*x + y*y + z*z); }
    Vec3 normalized() const { double l = length(); return l > 0 ? (*this)/l : *this; }
};
