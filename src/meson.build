project('ray-tracer', 'cpp')

# OpenMP dependency
omp = dependency('openmp', required: true, static: true)
add_global_arguments('-fopenmp', language : 'cpp')

executable('Main', 'main.cpp', dependencies: omp)