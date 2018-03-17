//
//  Prime Sum Parallel Program
//
//  Writen by Erik Sevre, October 2015
//
//  The goal of this program is to run a serial program to sum 1/p^2 for all  primes in 2-2^31-1
//  My code compares the runs with OpenMP optimizations, and with normal compiled versions.
//

#include <iostream>
#include "benchmark_runs.h"

using namespace std;

int main() {
    benchmark_serial_01();
    //benchmark_omp_01();
}

