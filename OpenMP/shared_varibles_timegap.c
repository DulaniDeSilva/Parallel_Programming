#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{


   // declaring numt and tid outside parallel block
   int numt, tid;


   #pragma omp parallel
   {
       int j;
       numt = omp_get_num_threads();
       tid = omp_get_thread_num();


       // introduce wait so that other threads get scheduled
       for(j=0; j<10000000; j++){
           printf("Hello World from thread %d of %d\n", tid, numt);
       }
   }


   return 0;
}
