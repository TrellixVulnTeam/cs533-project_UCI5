#include <rsa.h>
#include <x86intrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TRIALS 1000

int64_t timespec_diffns(struct timespec * a, struct timespec* b) {
    return (a->tv_nsec - b->tv_nsec) % 1000000000;
}

int main() {
    int64_t t0, t1;
    // struct timespec ts0, ts1;
    // struct timespec ts[TRIALS + 1];
    int64_t stat[TRIALS] = {};
    struct timespec slp_duration = {.tv_sec = 0, .tv_nsec=1};
    char *func = (char*)bignum_imultiply;
    char temp;

    for (int i = 0; i < TRIALS; ++i) {
        __asm__ volatile("clflush (%0)" ::"r"(((char *)&bignum_imultiply) + 0));
        // __asm__ volatile("clflush (%0)" ::"r"(((char *)&bignum_imultiply) + 128));
        t0 = _rdtsc();
        // clock_gettime(CLOCK_REALTIME, &ts0);
        //sleep(1);
        temp = *func;
        // clock_gettime(CLOCK_REALTIME, &ts1);
        t1 = _rdtsc();
        // stat[i] = timespec_diffns(&ts1, &ts0);
        stat[i] = t1 - t0;
    }

    printf("stat\n");
    for (int i = 0; i < TRIALS; ++i) {
        printf("%d:\t %ld\n", i, stat[i]);
    }

    FILE *fptr;
    fptr = fopen("../../analysis/lat.csv","w");
    for (int i = 0; i < TRIALS; i++) {
        fprintf(fptr, "%ld,", stat[i]);
    }

    return 0;
}
