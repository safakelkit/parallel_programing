#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    #pragma omp parallel for schedule(dynamic, 3)
    for (size_t i = 0; i < 40; i++)
    {
        printf("Dynamic Scheduling - Thread %d is working on iteration %zu\n", omp_get_thread_num(), i);
    }
    return 0;
}