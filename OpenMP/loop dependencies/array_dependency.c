#include <omp.h>
#include <stdio.h>

// Calculate prefix sums of an array with dependencies

int main() {
    int N = 10;
    int a[10], b[10];
    
    // Initialize arrays
    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }
    
    // Wrong way - dependency issues
    // array b is supposed to hold prefix sums of array a

    // This loop is not safe to parallelize, because:
    // Each computation of b[i] depends on the previous value b[i-1], which may or may not have been computed yet.
    // OpenMP may run i = 3 before i = 2 finishes, which breaks the chain of dependencies.

    #pragma omp parallel for
    for(int i = 1; i < N; i++) {
        b[i] = b[i-1] + a[i]; // Data dependency!
    }
    
    // Correct way - using temporary array

    // We need to use temp only because we don't want to modify the original array
    int temp[10];
    #pragma omp parallel for
    for(int i = 0; i < N; i++) {
        temp[i] = a[i];
    }
    
    // This loop is safe becasue it is sequential
    for(int i = 1; i < N; i++) {
        temp[i] += temp[i-1];
    }
    
    return 0;
}