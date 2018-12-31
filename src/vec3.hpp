#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

// 3D X,Y,Z Vector and RGB Color class
class vec3 {
    double e[3];

public:
    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    double r() const;
    double g() const;
    double b() const;

    const vec3 &operator+() const;
    vec3 operator-() const;

    double operator[](int i) const;
    double &operator[](int i);

    vec3 operator+(const vec3 &other) const;
    vec3 operator-(const vec3 &other) const;
    vec3 operator*(const vec3 &other) const;
    vec3 operator/(const vec3 &other) const;
    vec3 operator*(double t) const;
    vec3 operator/(double t) const;

    vec3 &operator+=(const vec3 &other);
    vec3 &operator-=(const vec3 &other);
    vec3 &operator*=(const vec3 &other);
    vec3 &operator/=(const vec3 &other);
    vec3 &operator*=(double t);
    vec3 &operator/=(double t);

    double length() const;
    double square_length() const;
    void make_unit_vector();
    vec3 to_unit() const;
    // Puts each element of this vector into the range 0.0 to 1.0
    vec3 to_unit_range() const;

    double dot(const vec3 &other) const;
    vec3 cross(const vec3 &other) const;

    friend std::istream &operator>>(std::istream &is, vec3 &t);
    friend std::ostream &operator<<(std::ostream &os, const vec3 &t);
};

vec3 operator*(double t, const vec3 &other);
vec3 operator/(double t, const vec3 &other);

#endif /* end of include guard: VEC3_HPP */
