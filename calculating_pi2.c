#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long steps = 100000000;
double step;

int main(int argc, const char* argv[]) {

    printf("omp_get_max_threads() = %d\n", omp_get_max_threads());

    int thread_counts[] = {1, 2, 4, 8};
    int num_cases = sizeof(thread_counts) / sizeof(thread_counts[0]);

    double pi = 0.0;
    step = 1.0 / (double)steps;

    for (int tc = 0; tc < num_cases; ++tc) {
        int nthreads = thread_counts[tc];
        omp_set_num_threads(nthreads);

        double start = omp_get_wtime();

        double sum = 0.0;
        #pragma omp parallel shared(pi)
        {
            #pragma omp for simd reduction(+:sum) schedule(simd:guided,10000)
            for (long i = 0; i < steps; ++i) {
                double x = (i + 0.5) * step;
                sum += 4.0 / (1.0 + x * x);
            }
            
            #pragma omp critical
            pi = sum * step;
        }

        double delta = omp_get_wtime() - start;

        printf("PI = %.16g computed in %.4g seconds with %d threads.\n", pi, delta, nthreads);    
    }

    return 0;
}