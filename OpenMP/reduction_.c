#include <stdio.h>
#include <omp.h>


int main(){
   double start_time = omp_get_wtime();


   double sum = 0.0;


   // #pragma omp parallel for
   // #pragma omp parallel for reduction(+:sum)
   for(int i=1; i<=1000; i++){
       sum += i;
   }


   double end_time = omp_get_wtime();
   printf("Time taken = %f seconds\n", end_time - start_time);
   printf("Sum = %f\n", sum);
}
