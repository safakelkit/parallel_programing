#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
        #pragma omp parallel for schedule(static,3) //single thread = iter_size/chunk_size
        for(int i = 0; i < 40; i++){
            printf("Static Scheduling - Chunk Size: 3 - Thread %d is working on iteration %d\n", omp_get_thread_num(), i);
        }
}

//Eğer static (static) yani default ise her 40/8 kadar iterasyon alır. Çünkü iter sayısı 40 ve thread sayısı 8'dir.
//Eğer static (static, 2) olursa her thread 2 iterasyon alır. Mesela thread 0 iterasyon 0 ve 1'i, thread 1 iterasyon 2 ve 3'ü alır. Tüm threadler bitince tekrar başa dönüp sırayla iterasyon alırlar.
//Eğer static (static, 3) olursa her thread 3 iterasyon alır. Mesela thread 0 iterasyon 0,1,2'yi, thread 1 iterasyon 3,4,5'i alır. Tüm threadler bitince tekrar başa dönüp sırayla iterasyon alırlar.
//static schedulingde chunk size belirlenirse her thread belirlenen chunk size kadar iterasyon alır ve tüm threadler bitince tekrar başa dönüp sırayla iterasyon alırlar.
//Aynı zamanda dağıtım baştan bellidir, runtime'da değişmez. Tüm threadler eşit sayıda iterasyon almaz. Mesela bu durumda thread 0,1,2,3,4 6şar iterasyon alırke thread 5 4 iterasyon alır ve thread 6 ve 7 3'er iterasyon alır.
//STATIC SCHEDULINGDE HER THREADIN ALACAĞI İTERASYONLAR BAŞTAN BELLİDİR VE RUNTIME'DA DEĞİŞMEZ.

// schedule(static, 2) kullanıldığında iterasyonlar 2'li chunk'lara bölünür.
// Bu chunk'lar thread'lere round-robin (sırayla) dağıtılır.
// Bir thread birden fazla 2'li chunk alabilir.
// Dağıtım döngü başlamadan önce belirlenir ve runtime'da değişmez.

//“Thread işi bitirince tekrar chunk alıyorsa bu hangi schedule?” = DYNAMIC
