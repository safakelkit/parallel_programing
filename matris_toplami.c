//2 100 milyon dizi iki tane her bir indeksi çarp
// srand ile random üretilen integer sayıyı double'a dönüştür, 0-1000 arası

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 100000000

int main(void) {
    double *a = (double*)malloc((size_t)N * sizeof(double));
    double *b = (double*)malloc((size_t)N * sizeof(double));
    double *c = (double*)malloc((size_t)N * sizeof(double));

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        a[i] = ((double)rand() / RAND_MAX) * 1000.0;
        b[i] = ((double)rand() / RAND_MAX) * 1000.0;
    }

    double t0 = omp_get_wtime();

    int max_threads = omp_get_max_threads();
    int counts[max_threads];              
    for (int i = 0; i < max_threads; i++) counts[i] = 0;

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp single
        {
            printf("Threads: %d\n", omp_get_num_threads());
        }

        #pragma omp for schedule(static)
        for (int i = 0; i < N; i++) {
            c[i] = a[i] * b[i];
            counts[tid]++;
        }
    }

    double t1 = omp_get_wtime();

    printf("Time = %.6f seconds\n\n", (t1 - t0));

    printf("\nFirst 5 elements of a:\n");
    for (int i = 0; i < 5; i++) {
        printf("a[%d] = %.6f\n", i, a[i]);
    }

    printf("\nFirst 5 elements of b:\n");
    for (int i = 0; i < 5; i++) {
        printf("b[%d] = %.6f\n", i, b[i]);
    }

    printf("\nFirst 5 elements of c:\n");
    for (int i = 0; i < 5; i++) {
        printf("c[%d] = %.6f\n", i, c[i]);
    }

    printf("\nLast 5 elements of a:\n");
    for (int i = N - 5; i < N; i++) {
        printf("a[%d] = %.6f\n", i, a[i]);
    }

    printf("\nLast 5 elements of b:\n");
    for (int i = N - 5; i < N; i++) {
        printf("b[%d] = %.6f\n", i, b[i]);
    }

    printf("\nLast 5 elements of c:\n");
    for (int i = N - 5; i < N; i++) {
        printf("c[%d] = %.6f\n", i, c[i]);
    }

    printf("\n");

    for (int t = 0; t < max_threads; t++) {
        if (counts[t] > 0) {
            printf("Thread %d processed %d elements\n", t, counts[t]);
        }
    }

    return 0;
}
