#include <cmath>

#include "vec3.hpp"

vec3::vec3() {}
vec3::vec3(double e0, double e1, double e2) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
}

double vec3::x() const {
    return e[0];
}
double vec3::y() const {
    return e[1];
}
double vec3::z() const {
    return e[2];
}

double vec3::r() const {
    return e[0];
}
double vec3::g() const {
    return e[1];
}
double vec3::b() const {
    return e[2];
}

const vec3 &vec3::operator+() const {
    return *this;
}
vec3 vec3::operator-() const {
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int i) const {
    return e[i];
}
double &vec3::operator[](int i) {
    return e[i];
}

vec3 vec3::operator+(const vec3 &other) const {
    return vec3(e[0] + other.e[0], e[1] + other.e[1], e[2] + other.e[2]);
}
vec3 vec3::operator-(const vec3 &other) const {
    return vec3(e[0] - other.e[0], e[1] - other.e[1], e[2] - other.e[2]);
}
vec3 vec3::operator*(const vec3 &other) const {
    return vec3(e[0] * other.e[0], e[1] * other.e[1], e[2] * other.e[2]);
}
vec3 vec3::operator/(const vec3 &other) const {
    return vec3(e[0] / other.e[0], e[1] / other.e[1], e[2] / other.e[2]);
}
vec3 vec3::operator*(double t) const {
    return vec3(e[0] * t, e[1] * t, e[2] * t);
}
vec3 vec3::operator/(double t) const {
    return vec3(e[0] / t, e[1] / t, e[2] / t);
}

vec3 &vec3::operator+=(const vec3 &other) {
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
}
vec3 &vec3::operator-=(const vec3 &other) {
    e[0] -= other.e[0];
    e[1] -= other.e[1];
    e[2] -= other.e[2];
    return *this;
}
vec3 &vec3::operator*=(const vec3 &other) {
    e[0] *= other.e[0];
    e[1] *= other.e[1];
    e[2] *= other.e[2];
    return *this;
}
vec3 &vec3::operator/=(const vec3 &other) {
    e[0] /= other.e[0];
    e[1] /= other.e[1];
    e[2] /= other.e[2];
    return *this;
}
vec3 &vec3::operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}
vec3 &vec3::operator/=(double t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

double vec3::length() const {
    return sqrt(square_length());
}
double vec3::square_length() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}
void vec3::make_unit_vector() {
    *this /= length();
}
vec3 vec3::to_unit() const {
    return *this / length();
}

double vec3::dot(const vec3 &other) const {
    return e[0] * other.e[0] + e[1] * other.e[1] + e[2] * other.e[2];
}

vec3 vec3::cross(const vec3 &other) const {
    return vec3(
        e[1] * other.e[2] - e[2] * other.e[1],
        -(e[0] * other.e[2] - e[2] * other.e[0]),
        e[0] * other.e[1] - e[1] * other.e[0]
    );
}

std::istream &operator>>(std::istream &is, vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}
std::ostream &operator<<(std::ostream &os, const vec3 &t) {
    os << t.e[0] << ' ' << t.e[1] << ' ' << t.e[2];
    return os;
}
