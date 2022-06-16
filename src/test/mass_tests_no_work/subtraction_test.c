// gcc -o test test.c $(pkg-config --libs --cflags gmp)
// -I/usr/local/Cellar/gmp/6.2.1_1/include -L/usr/local/Cellar/gmp/6.2.1_1/lib
// -lgmp

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../arithmetic/decimal_arithmetic.h"

void clear_it(mpz_t num1, mpz_t num2, mpz_t num1_helper, mpz_t num2_helper);
void generate_it(mpz_t num1_helper, mpz_t num1, mpz_t num2_helper, mpz_t num2,
                 gmp_randstate_t rstate);
void check_subtraction(mpz_t num1, int sign1, mpz_t num2, int sign2,
                      int *result1, int *result2);
void check_ret_value(int ret_value, mpz_t num1, mpz_t num2, mpz_t rop);
void create_infinity(mpz_t infinity);
void create_neg_infinity(mpz_t neg_infinity);
void convert_decimal_to_mpz(int *bits, mpz_t s21_rop);
void compare(mpz_t rop, mpz_t s21_rop);
void convert_mpz_to_decimal(mpz_t var, int *bits, int *result, int sign);

int main() {
  gmp_randstate_t rstate;
  gmp_randinit_default(rstate);
  gmp_randseed_ui(rstate, time(NULL));
  mpz_t num1_helper, num1;
  mpz_t num2_helper, num2;

  mpz_init(num1_helper);
  mpz_init(num1);
  mpz_init(num2_helper);
  mpz_init(num2);

  for (int i = 0; i < 10; i++) {
    generate_it(num1_helper, num1, num2_helper, num2, rstate);
  }
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
  srand(time(NULL));
  int two_pow1, two_pow2;
  int sign1, sign2;
  two_pow1 = rand() % 96;
  two_pow2 = rand() % 96;
  sign1 = rand() % 2;
  sign2 = rand() % 2;
  mpz_ui_pow_ui(num1_helper, 2, two_pow1);
  mpz_ui_pow_ui(num2_helper, 2, two_pow2);
  mpz_urandomm(num1, rstate, num1_helper);
  mpz_urandomm(num2, rstate, num2_helper);
  if (sign1)
    gmp_printf("mpz num1 is -%Zd\n", num1);
  else
    gmp_printf("mpz num1 is %Zd\n", num1);
  if (sign2)
    gmp_printf("mpz num2 is -%Zd\n", num2);
  else
    gmp_printf("mpz num2 is %Zd\n", num2);
  unsigned int bits1[3] = {0};
  int result1[4] = {0};
  convert_mpz_to_decimal(num1, bits1, result1, sign1);
  unsigned int bits2[3] = {0};
  int result2[4] = {0};
  convert_mpz_to_decimal(num2, bits2, result2, sign2);
  check_subtraction(num1, sign1, num2, sign2, result1, result2);
}

void check_subtraction(mpz_t num1, int sign1, mpz_t num2, int sign2,
                      int *result1, int *result2) {
  mpz_t rop;
  mpz_t s21_rop;
  mpz_init(rop);
  mpz_init(s21_rop);
  int ret_value;
  s21_decimal check_helper;
  s21_decimal a, b;
  for (int i = 0; i < 4; i++) {
    a.bits[i] = result1[i];
    b.bits[i] = result2[i];
  }
  if (sign1) mpz_mul_si(num1, num1, -1);
  if (sign2) mpz_mul_si(num2, num2, -1);
  ret_value = s21_sub(a, b, &check_helper);
  if (ret_value) {
    check_ret_value(ret_value, num1, num2, rop);
  } else {
    mpz_sub(rop, num1, num2);
    gmp_printf("\nmpz res is  %Zd\n", rop);
    gmp_printf("mpz bin res is\n");
    // print_bits(rop);
    convert_decimal_to_mpz(check_helper.bits, s21_rop);
    compare(rop, s21_rop);
  }
  mpz_clear(rop);
  mpz_clear(s21_rop);
}

void check_ret_value(int ret_value, mpz_t num1, mpz_t num2, mpz_t rop) {
  printf("i started check_ret_value func\n");
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
    mpz_sub(rop, num1, num2);
    create_neg_infinity(neg_infinity);
    if (mpz_cmp(neg_infinity, rop) > 0) {
      printf("true\n");
    } else {
      printf("not true");
    }
  } else {
    mpz_sub(rop, num1, num2);
    create_infinity(pos_infinity);
    if (mpz_cmp(rop, pos_infinity) > 0) {
      printf("true\n");
    } else {
      printf("not true");
    }
  }
  mpz_clear(pos_infinity);
  mpz_clear(neg_infinity);
}

void create_infinity(mpz_t infinity) {
  printf("i started create_infinity func\n");
  mpz_ui_pow_ui(infinity, 2, 96);
  mpz_sub_ui(infinity, infinity, 1);
}

void create_neg_infinity(mpz_t neg_infinity) {
  printf("i started neg_infinity func\n");
  mpz_ui_pow_ui(neg_infinity, 2, 96);
  mpz_sub_ui(neg_infinity, neg_infinity, 1);
  mpz_mul_si(neg_infinity, neg_infinity, -1);
}

void convert_decimal_to_mpz(int *bits, mpz_t s21_rop) {
  int reserve[3] = {0};
  int ten_pow = 0;
  mpz_t divide_by_10;
  mpz_init(divide_by_10);
  reserve[2] = bits[0];
  reserve[1] = bits[1];
  reserve[0] = bits[2];
  printf("\ns21 res converted to mpz compatible is\n");
  for (int k = 0; k < 3; k++) {
    for (int l = 31; l >= 0; l--) {
      if ((1 << l) & reserve[k])
        printf("\033[33m1\033[0m");
      else
        printf("0");
    }
    printf(" ");
  }
  printf("\n\nlast byte is ");
  for (int n = 31; n >= 0; n--) {
    if ((1 << n) & bits[3])
      printf("\033[33m1\033[0m");
    else
      printf("0");
  }
  int sign = (1 << 31) & bits[3];
  ten_pow = (bits[3] << 1) >> 17;
  printf("\nten_pow is %d\n", ten_pow);
  mpz_import(s21_rop, 3, 1, 4, -1, 0, reserve);
  if (sign) mpz_mul_si(s21_rop, s21_rop, -1);
  // if (ten_pow > 0) {
  //   mpz_ui_pow_ui(divide_by_10, 10, ten_pow);
  //   mpz_cdiv_q(s21_rop, s21_rop, divide_by_10);
  // }
  gmp_printf("\ns21 res is  %Zd\n", s21_rop);
  printf("s21 bin res is\n");
  // print_bits(s21_rop);
}

void compare(mpz_t rop, mpz_t s21_rop) {
  mpz_t diff, condition;
  mpz_init(diff);
  mpz_init(condition);
  mpz_sub(diff, rop, s21_rop);
  gmp_printf("diff is %Zd\n", diff);
  mpz_abs(diff, diff);
  if (mpz_cmp_d(diff, 0.0000001) < 0) {
    printf("\033[32mSUCCESS\033[0m\n");
  } else {
    printf("\033[31mFAIL\033[0m\n");
  }
  mpz_clear(diff);
  mpz_clear(condition);
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
  printf("\nbin num is\n");
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
  printf("\n");
}
