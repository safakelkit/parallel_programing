#include <omp.h>
#include <stdio.h>

static long steps = 100000000;
double step;

int main(int argc, const char* argv[]) {
    
    double pi = 0.0;
    step = 1.0 / (double)steps;

    omp_set_num_threads(8);

    double start = omp_get_wtime();

    double sum  = 0.0;
    #pragma omp parallel shared(step)
    {
        #pragma omp for simd schedule(simd:guided,10000) reduction(+:sum)
        for (long i = 0; i < steps; ++i) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical //bu kısım
        pi = sum * step;
    }

    double delta = omp_get_wtime() - start;

    printf("PI = %.16g\n", pi);
    printf("Time = %.6f seconds\n", delta);
    printf("Threads = %d\n", omp_get_max_threads());
    
    return 0;
}
