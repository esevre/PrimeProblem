cmake_minimum_required(VERSION 3.3)
project(PrimeProblem)

set(CMAKE_CXX_COMPILER /opt/local/bin/g++-mp-7)
set(CMAKE_C_COMPILER /opt/local/bin/gcc-mp-7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -msse3")

set(SOURCE_FILES main.cpp es_prime_functions.h benchmark_runs.h)
add_executable(PrimeProblem ${SOURCE_FILES})

