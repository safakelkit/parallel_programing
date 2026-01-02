#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
        #pragma omp parallel for schedule(static,3) //single thread = iter_size/chunk_size
        for(int i = 0; i < 40; i++){
            printf("Static Scheduling - Chunk Size: 3 - Thread %d is working on iteration %d\n", omp_get_thread_num(), i);
        }
}

// schedule(static, 2) kullanıldığında iterasyonlar 2'li chunk'lara bölünür.
// Bu chunk'lar thread'lere round-robin (sırayla) dağıtılır.
// Bir thread birden fazla 2'li chunk alabilir.
// Dağıtım döngü başlamadan önce belirlenir ve runtime'da değişmez.

//“Thread işi bitirince tekrar chunk alıyorsa bu hangi schedule?” = DYNAMIC
