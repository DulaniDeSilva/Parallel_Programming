#include <stdio.h>
#include <omp.h>

int tid;  // thread id shared by all the threads 
#pragma omp threadprivate(tid)     //each thread gets its own copy of tid

int main(int argc, char *argv[])
{
    int numt = 0;  //stores the total number of threads.

    //first parallel region.
    #pragma omp parallel default(shared)
    {
        int j;

        tid = omp_get_thread_num();    //save My thread ID

        if(tid == 0)         //only the master thread does this
        {
            for(j = 0; j < 10000000; j++);

            numt = omp_get_num_threads();   // total thread count
        }
    }   // htreads are destroyed, but htreadprivate variables surivie

    #pragma omp parallel default(shared)
    {
        printf("Hello World from thread %d out of %d\n", tid, numt);   //threadprivate preserves tid value from the first region
    }

    return 0;
}

//local threads data disappears after parallel region ends, but threadprivate(id) preserves each thread's copy between parallel regions. 
// each thread remembers its tid value from the first parallel region and uses it again in the second parallel region.


// key functions used
// omp_get_thread_num() - returns this thread id (0= master )
//omp_get_num_threads() - returns total number of active threads 
// #pragma omp threadprivate(var) - makes a global variable private per thread, preserving values across parallel regions 


//   "Ask students: 'How many Hello World lines do you expect?' (Answer: one per thread.)",
//     "Show that omp_get_thread_num() returns different values in different threads — there is NO shared 'current thread' variable.",
//     "Emphasise: thread IDs are 0-based. Thread 0 is always the master.",
//     "Run multiple times — the ORDER of the printfs may change each run because threads are concurrent.