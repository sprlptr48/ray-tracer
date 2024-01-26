/*26.01.2024 15.32 Friday
Define the vector class */
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
    double vec[3];

    vec3() : vec{0,0,0} {}
    vec3(double x, double y, double z) : vec{x, y, z} {}

    double x() const { return vec[0]; }
    double y() const { return vec[1]; }
    double z() const { return vec[2]; }

    vec3 operator-() const { return vec3(-vec[0], -vec[1], -vec[2]); }
    double operator[](int i) const { return vec[i]; }
    double& operator[](int i) { return vec[i]; }

    vec3& operator+=(const vec3 &v) {
        vec[0] += v.vec[0];
        vec[1] += v.vec[1];
        vec[2] += v.vec[2];
        return *this;
    }

    vec3& operator*=(double t) {
        vec[0] *= t;
        vec[1] *= t;
        vec[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
    }
};
using point3 = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.vec[0] << ' ' << v.vec[1] << ' ' << v.vec[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.vec[0] + v.vec[0], u.vec[1] + v.vec[1], u.vec[2] + v.vec[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.vec[0] - v.vec[0], u.vec[1] - v.vec[1], u.vec[2] - v.vec[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.vec[0] * v.vec[0], u.vec[1] * v.vec[1], u.vec[2] * v.vec[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.vec[0], t*v.vec[1], t*v.vec[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return v * (1/t);
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.vec[0] * v.vec[0]
         + u.vec[1] * v.vec[1]
         + u.vec[2] * v.vec[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.vec[1] * v.vec[2] - u.vec[2] * v.vec[1],
                u.vec[2] * v.vec[0] - u.vec[0] * v.vec[2],
                u.vec[0] * v.vec[1] - u.vec[1] * v.vec[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}


#endif //VEC3_H
