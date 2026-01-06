#include <stdio.h>
#include <omp.h>

#define N 10000

int main(void) {
    double a[N];
    double b[N];

    for (int i = 0; i < N; i++) {
        a[i] = (double)(i % 100) / 10.0;
        b[i] = (double)((i * 3) % 100) / 10.0;
    }

    double dot = 0.0;
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
            dot += a[i] * b[i];
            counts[tid]++;
        }
    }

    double t1 = omp_get_wtime();

    printf("Dot Product = %.6f\n", dot);
    printf("Time = %.6f seconds\n\n", (t1 - t0));

    for (int t = 0; t < max_threads; t++) {
        if (counts[t] > 0) {
            printf("Thread %d processed %d elements\n", t, counts[t]);
        }
    }

    return 0;
}
