#ifndef RSA_H_
#define RSA_H_

/* Accuracy with which we test for prime numbers using Solovay-Strassen
 * algorithm. 20 Tests should be sufficient for most largish primes */
#define ACCURACY 20

#define FACTOR_DIGITS 100
#define EXPONENT_MAX RAND_MAX
#define BUF_SIZE 1024

/* Initial capacity for a bignum structure. They will flexibly expand but this
 * should be reasonably high to avoid frequent early reallocs */
#define BIGNUM_CAPACITY 20

/* Radix and halfradix. These should be changed if the limb/word type changes */
#define RADIX 4294967296UL
#define HALFRADIX 2147483648UL

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * Basic limb type. Note that some calculations rely on unsigned overflow
 * wrap-around of this type. As a result, only unsigned types should be used
 * here, and the RADIX, HALFRADIX above should be changed as necessary. Unsigned
 * integer should probably be the most efficient word type, and this is used by
 * GMP for example.
 */
typedef unsigned int word;

/**
 * Structure for representing multiple precision integers. This is a base "word"
 * LSB representation. In this case the base, word, is 2^32. Length is the
 * number of words in the current representation. Length should not allow for
 * trailing zeros (Things like 000124). The capacity is the number of words
 * allocated for the limb data.
 */
typedef struct _bignum {
    int length;
    int capacity;
    word *data;
} bignum;

/**
 * Some forward delcarations as this was requested to be a single file.
 * See specific functions for explanations.
 */

extern bignum *bignum_init();
extern void bignum_deinit(bignum *b);
extern int bignum_iszero(bignum *b);
extern int bignum_isnonzero(bignum *b);
extern void bignum_copy(bignum *source, bignum *dest);
extern void bignum_fromstring(bignum *b, char *string);
extern void bignum_fromint(bignum *b, unsigned int num);
extern void bignum_print(bignum *b);
extern int bignum_equal(bignum *b1, bignum *b2);
extern int bignum_greater(bignum *b1, bignum *b2);
extern int bignum_less(bignum *b1, bignum *b2);
extern int bignum_geq(bignum *b1, bignum *b2);
extern int bignum_leq(bignum *b1, bignum *b2);
extern void bignum_iadd(bignum *source, bignum *add);
extern void bignum_add(bignum *result, bignum *b1, bignum *b2);
extern void bignum_isubtract(bignum *source, bignum *sub);
extern void bignum_subtract(bignum *result, bignum *b1, bignum *b2);
extern void bignum_imultiply(bignum *source, bignum *mult);
extern void bignum_multiply(bignum *result, bignum *b1, bignum *b2);
extern void bignum_idivide(bignum *source, bignum *div);
extern void bignum_idivider(bignum *source, bignum *div, bignum *remainder);
extern void bignum_remainder(bignum *source, bignum *div, bignum *remainder);
extern void bignum_imodulate(bignum *source, bignum *modulus);
extern void bignum_divide(bignum *quotient, bignum *remainder, bignum *b1,
                          bignum *b2);
extern void bignum_modpow(bignum *base, bignum *exponent, bignum *modulus,
                          bignum *result);
extern void bignum_gcd(bignum *b1, bignum *b2, bignum *result);
extern void bignum_inverse(bignum *a, bignum *m, bignum *result);
extern int bignum_jacobi(bignum *ac, bignum *nc);

#endif