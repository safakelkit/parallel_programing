#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    omp_set_num_threads(2);

    int tmp = 1;
    #pragma omp parallel private(tmp)
    {
        tmp += 1;

        printf("Thread %d: tmp = %d\n", omp_get_thread_num(), tmp);
    }

    return 0;
}