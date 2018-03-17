#!/usr/bin/python
import math

def create_vector(v):
    for i in range(3,10000):
        v.append(i)

def is_prime(n):
    if n == 2:
        return True
    elif n %2 == 0:
        return False
    for i in range(3,n-1, 2):
        if n%i == 0 :
            return False
    return True

def find_primes(vector):
    p = []
    for v in vector:
        if is_prime(v):
            p.append(v)
    return p


nums = []
create_vector(nums)
primes = find_primes(nums)

for p in primes:
    print(p) 
