cmake_minimum_required(VERSION 3.27)
project(ray-tracer)

find_package(OpenMP REQUIRED)

add_executable(Main main.cpp
        vec3.h color.h ray.h hittable.h
        sphere.h hittable_list.h camera.h
        interval.h rtweekend.h material.h)
target_link_libraries(Main PRIVATE OpenMP::OpenMP_CXX)
