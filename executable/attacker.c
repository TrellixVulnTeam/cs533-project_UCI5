#include <rsa.h>
#include <x86intrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TRIALS 1000

int main() {
    // int64_t t0, t1;
    int64_t timestamp[TRIALS+1] = {};
    char *func = (char*)bignum_imultiply;
    printf("bignum_imultiply vaddr: %p\n", bignum_imultiply);
    char temp;

    timestamp[0] = _rdtsc();
    for (int i = 0; i < TRIALS; ++i) {
        __asm__ volatile("clflush (%0)" ::"r"(((char *)&bignum_imultiply) + 0));
        // __asm__ volatile("clflush (%0)" ::"r"(((char *)&bignum_imultiply) + 128));
        // t0 = _rdtsc();
        // clock_gettime(CLOCK_REALTIME, &ts0);
        //sleep(1);
        temp = *func;
        // clock_gettime(CLOCK_REALTIME, &ts1);
        // t1 = _rdtsc();
        // stat[i] = timespec_diffns(&ts1, &ts0);
        timestamp[i+1] = _rdtsc();
    }

    // printf("stat\n");
    // for (int i = 0; i < TRIALS; ++i) {
    //     printf("%d:\t %ld\n", i, stat[i]);
    // }

    FILE *fptr;
    fptr = fopen("../../analysis/lat.csv","w");
    for (int i = 0; i < TRIALS+1; i++) {
        fprintf(fptr, "%ld,", timestamp[i]);
    }

    return 0;
}
