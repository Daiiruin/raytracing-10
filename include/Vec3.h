#pragma once
#include <cmath>

class Vec3 {
public:
    double x, y, z;
    Vec3(double x=0, double y=0, double z=0);

    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(double s) const;
    Vec3 operator/(double s) const;
    double dot(const Vec3& v) const;
    Vec3 normalized() const;
    static Vec3 cross(const Vec3& a, const Vec3& b);
};
