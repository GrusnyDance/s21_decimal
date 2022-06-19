/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../arithmetic/decimal_arithmetic.h"

// checkmk clean_mode=1 test.check > test.c

mpf_t num1, num2, s21_res;
mpz_t num1_helper, num2_helper;
s21_decimal first, second, res, ar_helper;

void clear_func(mpf_t num1, mpf_t num_2, mpf_t s21_res, mpz_t num1_helper,
                mpz_t num2_helper) {
  mpf_clear(num1);
  mpf_clear(num2);
  mpf_clear(s21_res);
  mpz_clear(num1_helper);
  mpz_clear(num2_helper);
}

void generate_float(int two_pow, int sub_helper, int sign, int floating_point,
                    mpf_t res, mpz_t num_helper) {
  mpz_ui_pow_ui(num_helper, 2, two_pow);
  if (sub_helper) mpz_sub_ui(num_helper, num_helper, sub_helper);
  if (sign) mpz_mul_si(num_helper, num_helper, -1);
  mpf_set_z(res, num_helper);
  mpf_div_ui(res, res, pow(10, floating_point));
}

void convert_to_dec(s21_decimal *array, mpz_t num, int sign, int floating_point,
                    s21_decimal *ar_helper) {
  set_null(array);
  set_null(ar_helper);
  mpz_export(ar_helper->bits, NULL, 1, 4, -1, 0, num);
  printf("THIS IS EXPORT\n");
  for (int j = 0; j < 4; j++) {
    for (int k = 31; k >= 0; k--) {
      if (ar_helper->bits[j] & (1 << k))
        printf("1");
      else
        printf("0");
    }
    printf(" ");
  }
  printf("\n");
  array->bits[0] = ar_helper->bits[2];
  array->bits[1] = ar_helper->bits[1];
  array->bits[2] = ar_helper->bits[0];
  if (sign) array->bits[3] |= 1 << 31;
  floating_point = floating_point << 16;
  array->bits[3] |= floating_point;
  printf("THIS IS FINAL TRANSFER\n");
  for (int j = 0; j < 4; j++) {
    for (int k = 31; k >= 0; k--) {
      if (array->bits[j] & (1 << k))
        printf("1");
      else
        printf("0");
    }
    printf(" ");
  }
  printf("\n");
}

void convert_to_mpf(s21_decimal result, mpf_t s21_res) {
  int reserve[3] = {0};
  int ten_pow = 0;
  mpz_t divide_by_10;
  mpz_t num_import;
  mpf_t divide_10_float;
  mpz_init(num_import);
  mpz_init(divide_by_10);
  mpf_init(divide_10_float);
  reserve[2] = result.bits[0];
  reserve[1] = result.bits[1];
  reserve[0] = result.bits[2];

  int sign = (1 << 31) & result.bits[3];
  ten_pow = (result.bits[3] << 1) >> 17;
  mpz_import(num_import, 3, 1, 4, -1, 0, reserve);
  if (sign) mpz_mul_si(num_import, num_import, -1);
  mpf_set_z(s21_res, num_import);
  if (ten_pow > 0) {
    mpz_ui_pow_ui(divide_by_10, 10, ten_pow);
    mpf_set_z(divide_10_float, divide_by_10);
    mpf_div(s21_res, s21_res, divide_10_float);
  }
  mpz_clear(divide_by_10);
  mpz_clear(num_import);
  mpf_clear(divide_10_float);
}

START_TEST(add_1) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(50, 1234567, 1, 6, num1, num1_helper);
  generate_float(80, 1234, 0, 3, num2, num2_helper);
  convert_to_dec(&first, num1_helper, 1, 6, &ar_helper);
  convert_to_dec(&second, num2_helper, 0, 3, &ar_helper);
  mpf_add(num1, num1, num2);
  s21_add(first, second, &res);
  convert_to_mpf(res, s21_res);
  mpf_sub(num1, num1, s21_res);
  mpf_abs(num1, num1);
  ck_assert_int_eq(mpf_cmp_ui(num1, 2) < 0, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(sub_1) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(67, 737465526, 0, 10, num1, num1_helper);
  generate_float(10, 7654, 1, 5, num2, num2_helper);
  convert_to_dec(&first, num1_helper, 0, 10, &ar_helper);
  convert_to_dec(&second, num2_helper, 1, 5, &ar_helper);
  mpf_sub(num1, num1, num2);
  s21_sub(first, second, &res);
  convert_to_mpf(res, s21_res);
  mpf_sub(num1, num1, s21_res);
  mpf_abs(num1, num1);
  ck_assert_int_eq(mpf_cmp_ui(num1, 2) < 0, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(mul_1) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(25, 737461, 1, 7, num1, num1_helper);
  generate_float(70, 957235, 1, 9, num2, num2_helper);
  convert_to_dec(&first, num1_helper, 1, 7, &ar_helper);
  convert_to_dec(&second, num2_helper, 1, 9, &ar_helper);
  mpf_mul(num1, num1, num2);
  s21_mul(first, second, &res);
  convert_to_mpf(res, s21_res);
  mpf_sub(num1, num1, s21_res);
  mpf_abs(num1, num1);
  ck_assert_int_eq(mpf_cmp_ui(num1, 2) < 0, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(mul_2) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(93, 0, 0, 7, num1, num1_helper);
  gmp_printf("num1 helper is %Zd\n", num1_helper);
  generate_float(93, 0, 0, 9, num2, num2_helper);
  gmp_printf("num2 helper is %Zd\n", num2_helper);
  convert_to_dec(&first, num1_helper, 0, 7, &ar_helper);
  convert_to_dec(&second, num2_helper, 0, 9, &ar_helper);
  int ret = s21_mul(first, second, &res);
  mpf_mul(num1, num1, num2);
  convert_to_mpf(res, s21_res);
  gmp_printf("s21 res is %Ff\n", s21_res);
  gmp_printf("or res is %Ff\n", num1);
  ck_assert_int_eq(ret, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
