#include "camera.h"
#include "vec3.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "color.h"

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    camera cam;
    cam.camName = 'a';

    cam.render(world); // this is done to remove const warnings in CLion

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 100;
    cam.samples_per_pixel = 16;
    cam.max_depth = 30;

    cam.fov = 50;
    cam.lookat = point3(-1, 0, -1);
    cam.lookfrom = point3(-2, 2, 1);
    cam.vup = vec3(0, 1 ,0);

    cam.defocus_angle = 10.0;
    cam.focus_dist    = 3.0;

    cam.render(world);
}
