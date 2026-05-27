#include <omp.h>
#include <stdio.h>

// Initializes private copies with original value

int main() {
    int x = 5;
    
    #pragma omp parallel firstprivate(x)
    {
        printf("Thread %d starts with x = %d\n", omp_get_thread_num(), x);
        x += omp_get_thread_num();    // each modifies its own copy 
        printf("Thread %d ends with x = %d\n", omp_get_thread_num(), x);
    }
    
    printf("Original x = %d\n", x); // Still 5
    return 0;
}

//  ["firstprivate(x) is like private(x) PLUS: the private copy is initialised to 5.",
//    "Thread 0 ends with x=5, Thread 1 ends with x=6, Thread 2 ends with x=7, etc.",
//    "The master's x is still 5 afterwards."],