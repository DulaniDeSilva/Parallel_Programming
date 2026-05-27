#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main() {
    int grid[N][N], dp[N][N];

    // Initialize grid with random values
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            grid[i][j] = rand() % 9 + 1;

    dp[0][0] = grid[0][0];

    // Initialize first row and column
    for(int i = 1; i < N; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
        dp[0][i] = dp[0][i-1] + grid[0][i];
    }

    // Wavefront parallelization
    for (int wave = 2; wave <= 2*N - 2; wave++) {
        #pragma omp parallel for
        for (int i = 1; i < N; i++) {
            int j = wave - i;
            if (j > 0 && j < N) {
                int min_prev = (dp[i-1][j] < dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
                dp[i][j] = min_prev + grid[i][j];
            }
        }
    }

    printf("Minimum path cost to reach (%d,%d): %d\n", N-1, N-1, dp[N-1][N-1]);
    return 0;
}
