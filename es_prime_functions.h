//
// Created by Erik Sevre on 10/14/15.
//
//  I want to use a "sieve" method, but I want to assist the sieve by pre-computing all the primes needed for the
// sieve intervals. The sieve should save time because our value for the interval is 2147483647, and the square root
// of this is about 46340, so by computing a list of all primes less than 46350 we have all possible prime factors for
// composite numbers in our range. This is a small computation in relation to the total size of the interval. I call
// this list of primes the "prime seeds" and I use them to speed up other computations.
//

#ifndef PRIMEPROBLEM_ES_PRIME_FUNCTIONS_H
#define PRIMEPROBLEM_ES_PRIME_FUNCTIONS_H

#include <cmath>

//
//  Header Declarations for functions we are using
//

//  We sum all the primes in the interval [begin - end], using primes, as the seeds, and we need the primes_size
double fast_sum_from_seeds(int begin, int end, int *primes, int primes_size);
void generate_prime_seeds(int *primes, int primes_size, int end);
bool is_prime_brute_force(int n);
int int_pow(int base, int exp);


//
//  THIS IS THE GOOD METHOD
//

double fast_sum_from_seeds(int begin, int end, int *primes, int primes_size){
    // we are only testing odd numbers, so if the user
    // inputs an even number, quickly correct this
    int start = begin + (begin%2==0 ? 1 : 0);
    if (start < 3) {
        start = 3; // never start before 3
    }
    //
    // The array will have length
    // [(end - start) + 1]/2 for end even, and
    // [(end - start) + 2]/2 for end odd, so:
    int array_length = (end-start + (end % 2 == 0 ? 1 : 2)) / 2;


    //
    //  Start the prime test for the seive
    //
    bool is_prime_at[array_length];
    for (int i = 0; i < array_length; ++i) {
        if ( (start + 2*i)%3 == 0 ){
            is_prime_at[i] = false;
        } else {
            is_prime_at[i] = true;
        }
    }
    //
    //  The above % test will mark 3 as not prime, so I correct that here
    //  since 3 can only be the first elemnt the fix is easy.
    //
    if (start == 3){
        is_prime_at[0] = true;
    }
    //
    //  index
    //
    for (int i = 0; i < primes_size; ++i) {
        int p = primes[i];
        //
        //  We stop our sieve if p^2 > end value of sieve
        //
        if (p > std::sqrt(end)){
            break;
        }
        int p2 = p*p;
        //
        //  To get the first index for a multiple of p (or p^2) after start
        // we will utilize the fact that -a%b = - (a mod b)
        //
        //  For p^2 < start, the index is: -start%p, the value is start/p + (start%p==0?0:1)
        //  For p^2 > start, the index is: -start%p2, the value is start/p2 + (start%p2==0?0:1)
        //
        //
        //int starting_multiple = (p2<start ? start/p+(start%p==0?0:1) : start/p2+(start%p2==0?0:1));
        int index;// = (p2 < start ? (p-start%p)/2 : (p2-start%p2)/2);
        if (p2 < start){
            index = (p-start%p)%2 == 0 ? (p-start%p)/2 : (2*p-start%p)/2;
        } else {
            index = (p2-start%p2)%2 == 0 ? (p2-start%p2)/2 : (2*p2-start%p)/2;
        }

        for (;index < array_length; index+=p) {
            is_prime_at[index] = false;
        }
    }

    //
    //  This is where we use the list generated above to add 1/p^2 for prime numbers in our list
    //
    double sum = 0.0;
    for (int i=0; i<array_length; ++i){
        if (is_prime_at[i]){
            int p = start+2*i;
            sum += 1/(static_cast<double>(p) * static_cast<double>(p));
        }
    }
    return sum;
}


void generate_prime_seeds(int *primes, int primes_size, int end=50000) {
    // want a list of all prime numbers from 1 to 2^31-1s
    // find first odd greater than begin
    int start = 3;
    int stop = end + (end%2==0 ? -1 : 0);
    int range = stop-start;
    int array_size = range/2 + 1;

    //
    //  initialize the arrays
    //
    bool is_prime_at[array_size];
    for (int i = 0; i < array_size; ++i) {
        is_prime_at[i] = true;
    }

    int prime_index = 0;
    for (int n = 3; n < end; n+=2) {
        if (is_prime_brute_force(n)){
            primes[prime_index] = n;
            ++prime_index;
        }
        if (prime_index >= primes_size){
            // prime index is too big, we have to stop
            break;
        }
    }
}

//
//  This is a semi-brute force primality check
//
//  We immediately know that 2 & 3 are prime, so we quick-check if the number is 2 or 3,
// then if it is a multiple of 2 or 3. Then to be a little bit more inteligent we use the
// fact that all primes bigger than 3 are either congruent to 1 mod 6 or 5 mod 6. This
// allows us to check
// from 5 ... sqrt(n) incrementing by 6, then
// from 7 ... sqrt(n) incrementing by 6
//
// This means we only need to check 1/3 of the numbers less than sqrt(n), so this is a
// little better than checking only odd numbers (1/2).
//
bool is_prime_brute_force(int n) {
    if (n == 2){
        return true;
    } else if (n%2 == 0){
        return false;
    } else if (n == 3){
        return true;
    } else if (n%3 == 0){
        return false;
    }
    for (int i = 5; i < std::sqrt(i); i+=6) {
        if (n % i == 0) {
            return false;
        }
    }
    for (int i = 7; i < std::sqrt(i); i+=6) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//
//  I created an integer pow function to make sure we aren't adversely effected by
// round-off error converting from a float/double to integer.
//
int int_pow(int base, int exp){
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

#endif //PRIMEPROBLEM_ES_PRIME_FUNCTIONS_H
