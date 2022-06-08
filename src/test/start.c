// gcc -o test test.c $(pkg-config --libs --cflags gmp)
// -I/usr/local/Cellar/gmp/6.2.1_1/include -L/usr/local/Cellar/gmp/6.2.1_1/lib
// -lgmp
#if defined(__linux__)
#include "./gmp-6.2.1/gmp.h"
#else
#include <gmp.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_bits(mpz_t var);
void convert_mpz_to_decimal(mpz_t var, int *bits, int *result, int sign);
void generate_it(mpz_t num1_helper, mpz_t num1, mpz_t num2_helper, mpz_t num2,
                 gmp_randstate_t rstate);
void check_addition(mpz_t num1, int sign1, mpz_t num2, int sign2, int *result1,
                    int *result2);

int main() {
  gmp_randstate_t rstate;
  gmp_randinit_default(rstate);
  gmp_randseed_ui(rstate, time(NULL));
  srand(time(NULL));
  mpz_t num1_helper, num1;
  mpz_t num2_helper, num2;

  mpz_inits(num1_helper, num1, num2_helper, num2);
  generate_it(num1_helper, num1, num2_helper, num2, rstate);
  gmp_randclear(rstate);
  mpz_clear(num1_helper);
  return 0;
}

void generate_it(mpz_t num1_helper, mpz_t num1, mpz_t num2_helper, mpz_t num2,
                 gmp_randstate_t rstate) {
  int two_pow1, two_pow2;
  int sign1, sign2;
  for (int i = 0; i < 1; i++) {
    two_pow1 = rand() % 97;
    two_pow2 = rand() % 97;
    sign1 = rand() % 2;
    sign2 = rand() % 2;
    mpz_ui_pow_ui(num1_helper, 2, two_pow1);
    mpz_ui_pow_ui(num2_helper, 2, two_pow2);
    mpz_urandomm(num1, rstate, num1_helper);
    mpz_urandomm(num2, rstate, num2_helper);
    if (sign1)
      gmp_printf("dec num1 is -%Zd\n", num1);
    else
      gmp_printf("dec num1 is %Zd\n", num1);
    if (sign2)
      gmp_printf("dec num1 is -%Zd\n", num2);
    else
      gmp_printf("dec num1 is %Zd\n", num2);
    // print_bits(num1);
    unsigned int bits1[3] = {0};
    int result1[4] = {0};
    convert_mpz_to_decimal(num1, bits1, result1, sign1);
    unsigned int bits2[3] = {0};
    int result2[4] = {0};
    convert_mpz_to_decimal(num2, bits2, result2, sign2);
    check_addition(num1, sign1, num2, sign2, result1, result2);
  }
}

void check_addition(mpz_t num1, int sign1, mpz_t num2, int sign2, int *result1,
                    int *result2){};

void print_bits(mpz_t var) {
  mpz_t tmp, res;
  mpz_init2(res, 128);
  mpz_init2(tmp, 128);
  mpz_ui_pow_ui(tmp, 2, 127);
  // gmp_printf("\n%Zd\n", tmp);
  for (int i = 127; i >= 0; i--) {
    mpz_ui_pow_ui(tmp, 2, i);
    mpz_and(res, tmp, var);
    if (mpz_cmp_ui(res, 0)) {
      printf("\033[33m1\033[0m");
    } else {
      printf("0");
    }
  }
  printf("\n");
  mpz_clear(tmp);
  mpz_clear(res);
}

void convert_mpz_to_decimal(mpz_t var, int *bits, int *result, int sign) {
  mpz_export(bits, NULL, 1, 4, -1, 0, var);
  int loc_count = -1;
  for (int i = 2; i >= 0; i--) {
    if (bits[i] && loc_count < 2) {
      result[++loc_count] = bits[i];
    }
  }
  if (sign) result[3] |= 1 << 31;
  printf("\narray is   ");
  for (int l = 0; l < 4; l++) {
    for (int m = 31; m >= 0; m--) {
      if ((1 << m) & result[l]) {
        printf("\033[33m1\033[0m");
      } else {
        printf("0");
      }
    }
    printf(" ");
  }
}
