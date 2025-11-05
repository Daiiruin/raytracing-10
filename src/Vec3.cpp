#include "Vec3.h"

Vec3::Vec3(double x, double y, double z): x(x), y(y), z(z) {}
Vec3 Vec3::operator+(const Vec3& v) const { return Vec3(x+v.x, y+v.y, z+v.z); }
Vec3 Vec3::operator-(const Vec3& v) const { return Vec3(x-v.x, y-v.y, z-v.z); }
Vec3 Vec3::operator*(double s) const { return Vec3(x*s, y*s, z*s); }
Vec3 Vec3::operator/(double s) const { return Vec3(x/s, y/s, z/s); }
double Vec3::dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
Vec3 Vec3::normalized() const {
    double m = std::sqrt(x*x + y*y + z*z);
    return Vec3(x/m, y/m, z/m);
}
Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
