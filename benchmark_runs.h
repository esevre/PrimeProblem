//
// Created by Erik Sevre on 10/14/15.
//

#ifndef PRIMEPROBLEM_BENCHMARK_RUNS_H
#define PRIMEPROBLEM_BENCHMARK_RUNS_H

//#include <omp.h>
#include <iostream>
#include "es_prime_functions.h"
#include <chrono>

//
//  Raw benchmark of my default serial code
//
void benchmark_serial_01(){
    std::chrono::high_resolution_clock::time_point start, stop;

    start = std::chrono::system_clock::now();
    //
    //  we want to sum 1/p^2 for all primes p < 2^31-1
    //
    const int max_value = int_pow(2,31)-1;

    const int prime_count = 5000;
    int primes[prime_count];
    generate_prime_seeds(primes, prime_count);

    const int num_intervals = 20000;
    const int interval_length = max_value / num_intervals;
    int begin = 3;
    int end = interval_length;
    double sum = 1/(2.0*2.0);
    for (int i = 0; i < num_intervals; ++i) {
        sum += fast_sum_from_seeds(begin, end, primes, prime_count);
        begin = end+1;
        end += interval_length;
    }
    // quick cleanup since our intervals don't divide perfectly
    sum += fast_sum_from_seeds(begin, max_value, primes, prime_count);


    //
    //  I print results after the timing, so the display time doesn't
    // interfere with computational performance.
    //
    stop = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << "sum is " << sum << std::endl;
    std::cout << "Serial wall time is : " << duration << std::endl;

}


////
////  Raw benchmark of my default OpenMP code
////
//void benchmark_omp_01(){
//    std::chrono::high_resolution_clock::time_point start, stop;
//
//    start = std::chrono::system_clock::now();
//
//
//    //
//    //  we want to sum 1/p^2 for all primes p < 2^31-1
//    //
//    int max_value = int_pow(2,31)-1;
//
//    const int prime_count = 5000;
//    int primes[prime_count];
//    generate_prime_seeds(primes, prime_count);
//
//    const int num_intervals = 20000;
//    const int interval = max_value / num_intervals;
//    int begin = 3;
//    int end = interval;
//    double sum = 1/(2.0*2.0);
//    double psum = 0.0;
//
//    const int num_procs = omp_get_max_threads();
//    int tid;
//
//    //  1_0     1_1      1_2      1_3      2_0      ...    num_intervals/num_procs
//    //  1       2        3        4                 ...    num_intervals  // serial
//    //  1 - 10, 11 - 20, 21 - 30, 31 - 40, 41 - 50, ...
//    //
//#pragma omp parallel shared(tid, sum) private(psum, begin, end) // omp parallel requires its own scope
//    {
//        omp_set_num_threads(num_procs);
//        tid = omp_get_thread_num();
//        psum = 0.0;
//        for (int i = 0; i < num_intervals/num_procs; ++i) {
//            begin = (num_procs*i + tid)*interval+1;
//            end = (num_procs*i + tid + 1)*interval;
//            psum += fast_sum_from_seeds(begin, end, primes, prime_count);
//        }
//        #pragma omp critical
//        { sum += psum; }
//
//    }
//    // quick cleanup since our intervals don't divide perfectly
//
//
//    //
//    //  I print results after the timing, so the display time doesn't
//    // interfere with computational performance.
//    //
//    stop = std::chrono::system_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
//    std::cout << "sum is " << sum << std::endl;
//    std::cout << "omp wall time is : " << duration << ", using " << num_procs << " threads" << std::endl;
//
//}
//
//void test(){
//    int num_procs = omp_get_max_threads();
//    int thread_num;
//#pragma omp parallel shared(thread_num) // omp parallel requires its own scope
//    {
//        omp_set_num_threads(num_procs);
//        thread_num = omp_get_thread_num();
//        printf("%d\n",thread_num);
//    }
//}


#endif //PRIMEPROBLEM_BENCHMARK_RUNS_H
