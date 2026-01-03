#include <omp.h>
#include <stdio.h>

static inline double heavy(int i, int j) {
    double x = (i + 1) * 0.001 + (j + 1) * 0.000001;
    for (int k = 0; k < 80; k++) x = x * 1.0000001 + 0.0000003;
    return x;
}

int main() {
    omp_set_num_threads(8);

    const int outer = 4;
    const int inner = 2000000;

    double sum = 0.0;
    double t = omp_get_wtime();

    #pragma omp parallel for collapse(2) reduction(+:sum) schedule(static, 2)
    for (int i = 0; i < outer; i++) { 
        for (int j = 0; j < inner; j++) {
            sum += heavy(i, j);
        }
    }

    t = omp_get_wtime() - t;
    printf("Time: =%.4f s, Sum=%.6f\n", t, sum);
    return 0;
}
