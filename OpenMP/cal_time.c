#include <stdio.h>
#include <omp.h>


int main(){
   double start_time = omp_get_wtime();


   int x = 10;
   #pragma omp parallel private(x)
   {
       x = omp_get_thread_num();
       printf("Thread %d: x = %d (shared)\n", omp_get_thread_num(), x);
   }


   double end_time = omp_get_wtime();
   printf("Time taken = %f seconds\n", end_time - start_time);
}
