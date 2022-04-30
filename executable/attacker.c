#include <rsa.h>
#include <x86intrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    int64_t t0, t1;

    bignum *base = bignum_init();
    bignum *pow = bignum_init();
    bignum *mod = bignum_init();
    bignum *result = bignum_init();

    bignum_fromstring(base, "2");
    bignum_fromstring(pow, "27");
    bignum_fromstring(mod, "65537");
    t0 = _rdtsc();
    bignum_modpow(base, pow, mod, result);
    t1 = _rdtsc();

    bignum_print(result);
    printf("\n");

    bignum_deinit(base);
    bignum_deinit(pow);
    bignum_deinit(mod);
    bignum_deinit(result);


    printf("t0 %ld t1 %ld\n", t0, t1);
    printf("elapsed %ld\n", t1 - t0);
    return 0;
}
