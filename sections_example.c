#include <omp.h>
#include <stdio.h>
#include <unistd.h> 

int main() {
    omp_set_num_threads(4);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp sections 
        {
            #pragma omp section 
            {
                sleep(3);
                printf("Section 1 done by thread %d\n", tid);
            }

            #pragma omp section
            {
                sleep(1);
                printf("Section 2 done by thread %d\n", tid);
            }
        }
        double delta = omp_get_wtime() - start;
        printf("After sections - thread %d, Time: %f\n", tid, delta);
    }

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        printf("\n\nSECOND PHASE w/NOWAIT CLAUSE\n\n");
        int tid = omp_get_thread_num();

        #pragma omp sections nowait
        {
            #pragma omp section 
            {
                sleep(3);
                printf("Section 1 done by thread %d\n", tid);
            }

            #pragma omp section
            {
                sleep(1);
                printf("Section 2 done by thread %d\n", tid);
            }
        }
        double delta = omp_get_wtime() - start;
        printf("After sections - thread %d, Time: %f\n", tid, delta);
    }
}
