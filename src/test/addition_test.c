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
#include "../arithmetic/decimal_arithmetic.h"

void clear_it(mpz_t num1, mpz_t num2, mpz_t num1_helper, mpz_t num2_helper);
void generate_it(mpz_t num1_helper, mpz_t num1, mpz_t num2_helper, mpz_t num2,
                 gmp_randstate_t rstate);
void check_addition(mpz_t num1, int sign1, mpz_t num2, int sign2, int *result1,
                    int *result2);
void check_ret_value(int ret_value, mpz_t num1, mpz_t num2, mpz_t rop);
void create_infinity(mpz_t infinity);
void create_neg_infinity(mpz_t neg_infinity);
void convert_decimal_to_mpz(int *bits, mpz_t s21_rop);
void compare(mpz_t rop, mpz_t s21_rop);
void print_bits(mpz_t var);
void convert_mpz_to_decimal(mpz_t var, int *bits, int *result, int sign);

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
  clear_it(num1, num2, num1_helper, num2_helper);
  return 0;
}

void clear_it(mpz_t num1, mpz_t num2, mpz_t num1_helper, mpz_t num2_helper) {
  mpz_clear(num1);
  mpz_clear(num2);
  mpz_clear(num1_helper);
  mpz_clear(num2_helper);
}

void generate_it(mpz_t num1_helper, mpz_t num1, mpz_t num2_helper, mpz_t num2,
                 gmp_randstate_t rstate) {
  int two_pow1, two_pow2;
  int sign1, sign2;
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
    gmp_printf("dec num2 is -%Zd\n", num2);
  else
    gmp_printf("dec num2 is %Zd\n", num2);
  unsigned int bits1[3] = {0};
  int result1[4] = {0};
  convert_mpz_to_decimal(num1, bits1, result1, sign1);
  unsigned int bits2[3] = {0};
  int result2[4] = {0};
  convert_mpz_to_decimal(num2, bits2, result2, sign2);
  check_addition(num1, sign1, num2, sign2, result1, result2);
}

void check_addition(mpz_t num1, int sign1, mpz_t num2, int sign2, int *result1,
                    int *result2){
  mpz_t rop;
  mpz_t s21_rop;
  mpz_inits(rop, s21_rop);
  int ret_value;
  s21_decimal check_helper;
  s21_decimal a, b;
  for (int i = 0; i < 4; i++) {
    a.bits[i] = result1[i];
    b.bits[i] = result2[i];
  }
  if (sign1) mpz_mul_si(num1, num1, -1);
  if (sign2) mpz_mul_si(num2, num2, -1);
  gmp_printf("dec num1 with sign is %Zd", num1);
  gmp_printf("dec num2 with sign is %Zd", num2);
  ret_value = s21_add(a, b, &check_helper);
  if (ret_value) {
    check_ret_value(ret_value, num1, num2, rop);
  } else {
    mpz_add(rop, num1, num2);
    convert_decimal_to_mpz(check_helper.bits, s21_rop);
    compare(rop, s21_rop);
  }
}

void check_ret_value(int ret_value, mpz_t num1, mpz_t num2, mpz_t rop) {
  mpz_t pos_infinity;
  mpz_t neg_infinity;
  mpz_inits(pos_infinity, neg_infinity);
  if (ret_value == 3) {
    if (!mpz_cmp_ui(num2, 0)) {
      printf("true if division by zero\n");
    } else {
      printf("not true if division by zero\n");
    }
  } else if (ret_value == 2) {
    mpz_add(rop, num1, num2);
    create_neg_infinity(neg_infinity);
    if (mpz_cmp(neg_infinity, rop) > 0) {
      printf("true\n");
    } else {
      printf("not true");
    }
  } else {
    mpz_add(rop, num1, num2);
    create_infinity(pos_infinity);
    if (mpz_cmp(rop, pos_infinity) > 0) {
      printf("true\n");
    } else {
      printf("not true");
    }
  }
}

void create_infinity(mpz_t infinity) {
  mpz_ui_pow_ui(infinity, 2, 96);
  mpz_sub_ui(infinity, infinity, 1);
}

void create_neg_infinity(mpz_t neg_infinity) {
  mpz_ui_pow_ui(neg_infinity, 2, 96);
  mpz_sub_ui(neg_infinity, neg_infinity, 1);
  mpz_mul_si(neg_infinity, neg_infinity, -1);
}

void convert_decimal_to_mpz(int *bits, mpz_t s21_rop) {
  for (int i = 0; i < 3; i++) {
    for (int j = 31; j >= 0; j--) {
      if ((1 << j) & bits[i]) printf("1");
      else printf("0");
    }
    printf(" ");
  }
  printf("\n");
  int reserve[2] = {0};
  reserve[2] = bits[0];
  reserve[1] = bits[1];
  reserve[0] = bits[2];
  mpz_import(s21_rop, 4, 1, 4, -1, 0, reserve);
  if (bits[3] < 0) mpz_mul_si(s21_rop, s21_rop, -1);
  print_bits(s21_rop);
}

void compare(mpz_t rop, mpz_t s21_rop) {
  mpz_t diff, condition;
  mpz_inits(diff, condition);
  mpz_sub(diff, rop, s21_rop);
  gmp_printf("diff is %Zd\n", diff);
  mpz_abs(diff, diff);
  if (mpz_cmp_d(diff, 0.0000001) < 0) {
    printf("it works\n");
  } else {
    printf("it does not work\n");
  }
}

void print_bits(mpz_t var) {
  mpz_t tmp, res;
  mpz_init2(res, 128);
  mpz_init2(tmp, 128);
  mpz_ui_pow_ui(tmp, 2, 127);
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
