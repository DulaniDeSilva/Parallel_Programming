#include <stdio.h>
#include <omp.h>


int main(){
   int size =  1000000;
   int A[size];


   double start_time = omp_get_wtime();


   #pragma omp parallel for
   for(int i=0; i<size;i++){
       A[i] = i * i;
   }


   double end_time = omp_get_wtime();
   printf("Time taken = %f seconds\n", end_time - start_time);

   return 0;
}
