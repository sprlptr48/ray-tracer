//
// Created by eee on 01/02/2024.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
    sphere(const point3& _center, const double _radius, shared_ptr<material> _mat):
        center(_center), radius(_radius), mat(_mat) {}

    // Returns true if the ray hits this sphere
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);
        auto root = (-half_b - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.p = r.at(root); // root is our new t
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.t = root;
        rec.mat = mat;

        return true;
    }


private:
    point3 center;
    double radius;
    shared_ptr<material> mat;

};

#endif //SPHERE_H
