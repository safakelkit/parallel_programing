// Matris-Vektör Çarpımı - GPU Versiyonu (OpenMP Target)
#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

int main(int argc, char **argv) {
    int n = 10000;
    if (argc >= 2) n = atoi(argv[1]);

    double *A = new double[(size_t)n * n];
    double *x = new double[n];
    double *y = new double[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = 1.0;
        }
    }
    for (int j = 0; j < n; j++) {
        x[j] = 1.0;
    }

    double t0 = omp_get_wtime();

    #pragma omp target map(to: A[0:n*n], x[0:n]) map(from: y[0:n])
    {
        #pragma omp teams
        {
            #pragma omp distribute parallel for
            for (int i = 0; i < n; i++) {
                double sum = 0.0;
                for (int j = 0; j < n; j++) {
                    sum += A[i * n + j] * x[j];
                }
                y[i] = sum;
            }
        }
    }

    double t1 = omp_get_wtime();

    cout << "n=" << n << " (kare matris)\n";
    cout << "y[0]=" << y[0] << ", y[n-1]=" << y[n-1] << "\n";
    cout << "time=" << (t1 - t0) << " s\n";

    delete[] A;
    delete[] x;
    delete[] y;
    return 0;
}
