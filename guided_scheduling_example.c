#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    #pragma omp parallel for schedule(guided, 3) ordered
    for(int i = 0; i < 40; i++){
        printf("Guided Scheduling - Thread %d is working on iteration %d\n", omp_get_thread_num(), i);
    }
    return 0;
}