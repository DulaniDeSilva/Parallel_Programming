#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{


   // declaring numt and tid outside parallel block
   int numt, tid;


   // specifying private and shared variables
   #pragma omp parallel private (tid) shared (numt)
   {


       // Get the total number of OMP threads
       numt = omp_get_num_threads();


       // Get the thread id of this thread
       tid = omp_get_thread_num();




       // print "Hello world" along with thread id and number of threads
       printf("Hello World from thread %d of %d.\n", tid, numt);
   }


   return 0;
}
