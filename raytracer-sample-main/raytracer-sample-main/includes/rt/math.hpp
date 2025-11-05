#pragma once
#include <algorithm>
#include <cmath>

namespace rt {

constexpr double PI  = 3.14159265358979323846;
constexpr double EPS = 1e-4;

struct Vec3 {
    double x=0, y=0, z=0;
    Vec3() = default;
    Vec3(double X,double Y,double Z):x(X),y(Y),z(Z){}
    Vec3 operator+(const Vec3& o) const { return {x+o.x,y+o.y,z+o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x-o.x,y-o.y,z-o.z}; }
    Vec3 operator*(double s)      const { return {x*s,y*s,z*s}; }
    Vec3 operator*(const Vec3& o) const { return {x*o.x,y*o.y,z*o.z}; }
    Vec3 operator/(double s)      const { return {x/s,y/s,z/s}; }
};

inline double dot(const Vec3&a,const Vec3&b){ return a.x*b.x+a.y*b.y+a.z*b.z; }
inline Vec3 cross(const Vec3&a,const Vec3&b){
    return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}
inline Vec3 normalize(const Vec3& v){ double n=std::sqrt(dot(v,v)); return n>0? v/n : v; }

inline Vec3 clamp01(const Vec3& c){
    auto cl=[](double v){ return std::max(0.0,std::min(1.0,v)); };
    return {cl(c.x),cl(c.y),cl(c.z)};
}

}
