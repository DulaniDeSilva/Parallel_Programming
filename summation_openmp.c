// compute the sum of all elements in an array
// elements  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

#include <stdio.h>
#include <omp.h>

int main(){

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i =0; i<10; i++){
        sum += arr[i];
    }

    printf("Sum = %d\n", sum);

    return 0;
}