#include <omp.h>
#include <stdio.h>

// Variable is shared among all threads

int main() {
    int shared_counter = 0;
    
    #pragma omp parallel shared(shared_counter)  // shared counter - shared between the threads
    {
        #pragma omp atomic    
        shared_counter++;       // safe becuase of atomic, only one thread updates at a time. prevents race condition.   
        
        #pragma omp barrier  // all threads must  wait here until every thread finishes incrementing the counter. 
        if(omp_get_thread_num() == 0) {
            printf("Final counter value: %d\n", shared_counter);
        }
    }

    return 0;
}


//all threads share the same vairable
// every thread increments it once
// atomic ensures correct updated
// barrier ensures all increaments finish before printing  
//without atomic the output may become incorrect due to multiple threads updating the same time. 

//  ["Without the #pragma omp atomic, multiple threads would read-modify-write shared_counter at the same time, producing INCORRECT results. Show students both versions."],