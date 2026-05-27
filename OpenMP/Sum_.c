// with data scope


#include <stdio.h>
#include <omp.h>


#define N 1000


int main()
{
 int array[N];
 int sum = 0;
  for(int i=0; i<N; ++i){
   array[i] = 1;
 }
  #pragma omp parallel shared(array) private(sum)
 {
   int local_sum =0;


   #pragma omp for
   for(int i=0; i<N; ++i){
     local_sum += array[i];
   }


   #pragma omp atomic
   sum += local_sum;
 }
  printf("Sum: %d\n", sum);
 return 0;
 }


