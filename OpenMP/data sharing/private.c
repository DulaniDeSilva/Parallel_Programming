#include <omp.h>
#include <stdio.h>

// Variables are private to each thread

int main() {
    int i = 100;    //original value. 
    
    #pragma omp parallel private(i)
    {
        i = omp_get_thread_num(); // Each thread gets its own copy, its own i
        printf("Thread %d has i = %d\n", omp_get_thread_num(), i);
    }
    
    printf("After parallel region, i = %d\n", i); // Original value preserved
    return 0;
}


//  ["private(i) gives each thread an UNINTIALISED separate copy of i.",
//    "The original value of i (100) is NOT copied in.",
//    "After the parallel region, i is still 100 — the private copies vanish."],