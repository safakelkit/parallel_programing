// Dot Product (Nokta Çarpımı) - GPU Versiyon (OpenMP Target)

#include <iostream>
#include <omp.h>
using namespace std;

const int N = 10000;

int main() {
    double a[N], b[N];

    for (int i = 0; i < N; i++) {
        a[i] = (double)(i % 100) / 10.0;
        b[i] = (double)((i * 3) % 100) / 10.0;
    }

    double dot = 0.0;
    double t0 = omp_get_wtime();

    #pragma omp target map(to: a[0:N], b[0:N]) map(tofrom: dot)
    {
        #pragma omp teams 
        {
            #pragma omp distribute parallel for reduction(+:dot)
            for (int i = 0; i < N; i++) {
                dot += a[i] * b[i];
            }
        }
    }

    double t1 = omp_get_wtime();

    cout << "Dot Product = " << dot << endl;
    cout << "Time = " << (t1 - t0) << " seconds" << endl;

    return 0;
}
