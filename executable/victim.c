#include <stdio.h>
#include <stdbool.h>
#include <netdb.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>
#include <rsa.h>

int main() {
    bignum * base = bignum_init();
    bignum * pow = bignum_init();
    bignum * mod = bignum_init();
    bignum* result = bignum_init();

    bignum_fromstring(base, "2");
    bignum_fromint(pow, 39843);
    bignum_fromstring(mod, "65537");

    bignum_modpow(base, pow, mod, result);
    bignum_print(result);
    printf("\n");

    bignum_deinit(base);
    bignum_deinit(pow);
    bignum_deinit(mod);
    bignum_deinit(result);

    return 0;
}