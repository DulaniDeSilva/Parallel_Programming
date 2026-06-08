// Maximum value of an array
#include <stdio.h>
#include <omp.h>

int main(){
    int arr[8] = {3, 1, 4, 1, 5 ,9, 2, 6};
    int max_val = arr[0]; //consider the first element. 

    #pragma omp parallel for reduction(max:max_val)
    for(int i=1; i<8;i++){
        if(arr[i] > max_val)
            max_val = arr[i];
    }
    printf("Maximum value: %d\n", max_val);
    return 0;
}