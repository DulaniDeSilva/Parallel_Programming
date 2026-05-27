#include <stdio.h>
#define N 1000

int main()
{
 int array[N];
 int sum = 0;
  for(int i=0; i<N; ++i){
   array[i] = 1;
 }
  #pragma omp parallel for
 for(int i =0; i<N; ++i){
   sum+= array[i];
 }
  printf("Sum: %d\n", sum);
 return 0;
 }


