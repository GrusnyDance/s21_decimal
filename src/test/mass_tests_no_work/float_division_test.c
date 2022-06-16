// gcc -o test test.c $(pkg-config --libs --cflags gmp)
// -I/usr/local/Cellar/gmp/6.2.1_1/include -L/usr/local/Cellar/gmp/6.2.1_1/lib
// -lgmp

#include <gmp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../arithmetic/decimal_arithmetic.h"

void clear_it(mpz_t num1, mpz_t num2, mpz_t num1_helper, mpz_t num2_helper);
void generate_it(mpz_t num1_helper, mpz_t num1, mpz_t num2_helper, mpz_t num2,
                 gmp_randstate_t rstate);
void check_division(mpf_t num1, mpf_t num2, int *result1, int *result2);
void check_ret_value(int ret_value, mpf_t num1, mpf_t num2, mpf_t rop);
void create_infinity(mpz_t infinity);
void create_neg_infinity(mpz_t neg_infinity);
void convert_decimal_to_mpf(int *bits, mpz_t s21_rop, mpf_t s21_final);
void compare(mpf_t rop, mpf_t s21_rop);
// void print_bits(mpf_t var);
void convert_mpz_to_decimal(mpz_t var, int *bits, int *result, int sign,
                            unsigned int floating_point);

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
  srand(time(NULL));
  int two_pow1, two_pow2;
  int sign1, sign2;
  unsigned int floating_point1, floating_point2;
  two_pow1 = rand() % 96;
  two_pow2 = rand() % 96;
  sign1 = rand() % 2;
  sign2 = rand() % 2;
  floating_point1 = rand() % 15;
  floating_point2 = rand() % 15;
  mpf_t float_num1, float_num2;
  mpf_init(float_num1);
  mpf_init(float_num2);

  mpz_ui_pow_ui(num1_helper, 2, two_pow1);
  mpz_ui_pow_ui(num2_helper, 2, two_pow2);
  mpz_urandomm(num1, rstate, num1_helper);
  mpz_urandomm(num2, rstate, num2_helper);
  // gmp_printf("\nint num1 is %Zd\n", num1);  // final int
  // gmp_printf("int num2 is %Zd\n", num2);    // final int
  unsigned int bits1[3] = {0};
  int result1[4] = {0};
  convert_mpz_to_decimal(num1, bits1, result1, sign1, floating_point1);
  unsigned int bits2[3] = {0};
  int result2[4] = {0};
  convert_mpz_to_decimal(num2, bits2, result2, sign2, floating_point2);
  if (sign1) mpz_mul_si(num1, num1, -1);
  if (sign2) mpz_mul_si(num2, num2, -1);
  mpf_set_z(float_num1, num1);  // convert to float, precision lost
  mpf_set_z(float_num2, num2);
  mpf_div_ui(float_num1, float_num1, pow(10, floating_point1));
  mpf_div_ui(float_num2, float_num2, pow(10, floating_point2));
  gmp_printf("\nnum1 is %.28Ff\n", float_num1);  // final float
  gmp_printf("num2 is %.28Ff\n", float_num2);    // final float

  check_division(float_num1, float_num2, result1, result2);
  mpf_clear(float_num1);
  mpf_clear(float_num2);
}

void check_division(mpf_t num1, mpf_t num2, int *result1, int *result2) {
  mpf_t rop;
  mpz_t s21_rop;
  mpf_t s21_final;
  mpf_init(s21_final);
  mpf_init(rop);
  mpz_init(s21_rop);
  int ret_value;
  s21_decimal check_helper;
  s21_decimal a, b;
  for (int i = 0; i < 4; i++) {
    a.bits[i] = result1[i];
    b.bits[i] = result2[i];
  }
  ret_value = s21_div(a, b, &check_helper);
  if (ret_value) {
    check_ret_value(ret_value, num1, num2, rop);
  } else {
    mpf_div(rop, num1, num2);
    gmp_printf("\nmpf res is %.28Ff\n", rop);
    convert_decimal_to_mpf(check_helper.bits, s21_rop, s21_final);
    compare(rop, s21_final);
  }
  mpf_clear(rop);
  mpz_clear(s21_rop);
  mpf_clear(s21_final);
}

void check_ret_value(int ret_value, mpf_t num1, mpf_t num2, mpf_t rop) {
  printf("\n\033[31mEXTREME CASE CHECK\033[0m\n");
  mpz_t pos_infinity;
  mpz_t neg_infinity;
  mpf_t pos_infinity_float;
  mpf_t neg_infinity_float;
  mpz_init(pos_infinity);
  mpz_init(neg_infinity);
  mpf_init(pos_infinity_float);
  mpf_init(neg_infinity_float);
  if (ret_value == 3) {
    if (!mpf_cmp_ui(num2, 0)) {
      printf("true if division by zero\n");
    } else {
      printf("not true if division by zero\n");
    }
  } else if (ret_value == 2) {
    printf("negative infinity\n");
    if (mpf_cmp_ui(num2, 0)) {
      mpf_div(rop, num1, num2);
      gmp_printf("mpf result is %.28Ff\n", rop);
      create_neg_infinity(neg_infinity);
      mpf_set_z(neg_infinity_float, neg_infinity);
      gmp_printf("neg infinity is %.28Ff\n", neg_infinity_float);
      if (mpf_cmp(neg_infinity_float, rop) > 0) {
        printf("\033[32mCHECK PASSED\033[0m\n");
      } else {
        printf("\033[31mCHECK NOT PASSED\033[0m\n");
      }
    } else {
      printf("\033[31mCHECK NOT PASSED\033[0m\n");
    }
  } else if (ret_value == 1) {
    printf("positive infinity\n");
    mpf_div(rop, num1, num2);
    gmp_printf("mpf result is %.28Ff\n", rop);
    create_infinity(pos_infinity);
    mpf_set_z(pos_infinity_float, pos_infinity);
    gmp_printf("pos infinity is %.28Ff\n", pos_infinity_float);
    if (mpf_cmp(rop, pos_infinity_float) > 0) {
      printf("\033[32mCHECK PASSED\033[0m\n");
    } else {
      printf("\033[31mCHECK NOT PASSED\033[0m\n");
    }
  }
  mpz_clear(pos_infinity);
  mpz_clear(neg_infinity);
  mpf_clear(pos_infinity_float);
  mpf_clear(neg_infinity_float);
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

void convert_decimal_to_mpf(int *bits, mpz_t s21_rop, mpf_t s21_final) {
  int reserve[3] = {0};
  int ten_pow = 0;
  mpz_t divide_by_10;
  mpf_t divide_10_float;
  mpz_init(divide_by_10);
  mpf_init(divide_10_float);
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
  printf("\nlast byte is ");
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
  mpf_set_z(s21_final, s21_rop);
  if (ten_pow > 0) {
    mpz_ui_pow_ui(divide_by_10, 10, ten_pow);
    mpf_set_z(divide_10_float, divide_by_10);
    mpf_div(s21_final, s21_final, divide_10_float);
  }
  gmp_printf("\ns21 res is %.28Ff\n", s21_final);
  // print_bits(s21_final);
  mpf_clear(divide_10_float);
  mpz_clear(divide_by_10);
}

void compare(mpf_t rop, mpf_t s21_rop) {
  mpf_t diff, condition;
  mpf_init(diff);
  mpf_init(condition);
  mpf_sub(diff, rop, s21_rop);
  gmp_printf("diff is    %.28Ff\n", diff);
  mpf_abs(diff, diff);
  if (mpf_cmp_d(diff, 2) < 0) {
    printf("\033[32mSUCCESS\033[0m\n");
  } else {
    printf("\033[31mFAIL\033[0m\n");
  }
  mpf_clear(diff);
  mpf_clear(condition);
}

// void print_bits(mpf_t var) {
//   mpz_t tmp, res;
//   mpz_init2(res, 192);
//   mpz_init2(tmp, 192);
//   mpz_ui_pow_ui(tmp, 2, 191);
//   for (int i = 191; i >= 0; i--) {
//     mpz_ui_pow_ui(tmp, 2, i);
//     mpz_and(res, tmp, var);
//     if (mpz_cmp_ui(res, 0)) {
//       printf("\033[33m1\033[0m");
//     } else {
//       printf("0");
//     }
//   }
//   printf("\n");
//   mpz_clear(tmp);
//   mpz_clear(res);
// }

void convert_mpz_to_decimal(mpz_t var, int *bits, int *result, int sign,
                            unsigned int floating_point) {
  mpz_export(bits, NULL, 1, 4, -1, 0, var);
  int loc_count = -1;
  for (int i = 2; i >= 0; i--) {
    if (bits[i] && loc_count < 2) {
      result[++loc_count] = bits[i];
    }
  }
  if (sign) result[3] |= 1 << 31;
  // вписать в бинарном виде степень десятки, которая есть в десятичном
  floating_point = floating_point << 16;
  result[3] |= floating_point;
  // printf("last int is ");
  // for (int m = 31; m >= 0; m--) {
  //   if ((1 << m) & result[3]) {
  //     printf("\033[33m1\033[0m");
  //   } else {
  //     printf("0");
  //   }
  // }
  // printf(" ");
  // printf("\n");
}
