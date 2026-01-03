#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int n = 16000;                
    if (argc >= 2) n = atoi(argv[1]);

    double *A = (double*)malloc((size_t)n * n * sizeof(double));
    double *x = (double*)malloc((size_t)n * sizeof(double));
    double *y = (double*)malloc((size_t)n * sizeof(double));

    for (int j = 0; j < n; ++j)
        x[j] = 1.0;

    for (int i = 0; i < n; ++i) {
        int row = i * n;
        for (int j = 0; j < n; ++j) {
            A[row + j] = 1.0;
        }
    }

    int thread_counts[] = {1, 2, 4, 8};
    int num_cases = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int tc = 0; tc < num_cases; ++tc) {
        int nthreads = thread_counts[tc];
        omp_set_num_threads(nthreads);

        double start = omp_get_wtime();

        #pragma omp parallel
        {
            #pragma omp for schedule(static)
            for (int i = 0; i < n; ++i) {
                double sum = 0.0;
                int row = i * n;

                #pragma omp simd reduction(+:sum)
                for (int j = 0; j < n; ++j) {
                    sum += A[row + j] * x[j];
                }
                y[i] = sum;
            }
        }
        double elapsed = omp_get_wtime() - start;

        printf("threads = %d, time = %.4f seconds\n",
               nthreads, elapsed);
    }

    free(A);
    free(x);
    free(y);

    return 0;
}
