#pragma once

#include "utils.hpp"
#include <cmath>
#include <iostream>

using std::sqrt;

class Color;
class Vec3
{
  public:
    double e[3];

    Vec3() : e{0, 0, 0} {}
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    Vec3 &operator+=(const Vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3 &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3 &operator/=(double t) { return *this *= 1 / t; }

    double length() const { return sqrt(length_squared()); }

    double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    static Vec3 random() { return Vec3(utils::random_double(), utils::random_double(), utils::random_double()); }

    static Vec3 random(double min, double max)
    {
        return Vec3(utils::random_double(min, max), utils::random_double(min, max), utils::random_double(min, max));
    }

    static Vec3 random_gaussian(double min, double max)
    {
        return Vec3(utils::random_gaussian(min, max), utils::random_gaussian(min, max),
                    utils::random_gaussian(min, max));
    }

    operator Color() const;
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using Point3 = Vec3;

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) { return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]); }

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) { return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]); }

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) { return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]); }

inline Vec3 operator*(double t, const Vec3 &v) { return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]); }

inline Vec3 operator*(const Vec3 &v, double t) { return t * v; }

inline Vec3 operator/(const Vec3 &v, double t) { return (1 / t) * v; }

inline double dot(const Vec3 &u, const Vec3 &v) { return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; }

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(const Vec3 &v) { return v / v.length(); }

inline Vec3 random_in_unit_sphere()
{
    // https://math.stackexchange.com/questions/1585975/how-to-generate-random-points-on-a-sphere
    auto p = Vec3::random_gaussian(-1, 1);
    return p;

    // Vec3 p;
    // do
    // {
    //     p = Vec3::random_gaussian(-1, 1);
    // } while (p.length_squared() >= 1);
    // return p;
}

inline Vec3 random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

inline Vec3 random_on_hemisphere(const Vec3 &normal)
{
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}