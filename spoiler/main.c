#include <stdio.h>
#include <malloc.h>

int* main() {
    int cycles_high, cycles_low, cycles_high1, cycles_low1;

    int PAGE_COUNT  = 1000;
    int PAGE_SIZE   = 4096;
    int w           = 64;
    int *buffer     = (int*)malloc(PAGE_SIZE*PAGE_COUNT*sizeof(int));
    int DATA        = 5;
    int X           = 102; //The page that we want to read
    int *measure    = (int*)malloc(PAGE_COUNT*sizeof(int));

    for (int p = w; p <= PAGE_COUNT; p++){
        for (int i = w; i >= 0; i--){
            buffer[(p-i)*PAGE_SIZE] = DATA;
        }
        __asm__("CPUID\n\t"
         "RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
        //t1 = _rdtscp();

        DATA = buffer[X * PAGE_SIZE];//Note: We want to read information from the buffer and store to the same DATA parameter which can be used in the store instruction above
        
        __asm__("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
        //t2 = _rdtscp();
        
        measure[p] = cycles_low1-cycles_low;
        printf("%d\n", measure[p]);
    }
    return measure;
}
