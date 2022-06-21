/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>
#include <gmp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "./arithmetic/decimal_arithmetic.h"

mpf_t num1, num2, s21_res;
mpz_t num1_helper, num2_helper;
s21_decimal first, second, res, ar_helper;

void clear_func(mpf_t num1, mpf_t num2, mpf_t s21_res, mpz_t num1_helper,
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
  int loc_count = -1;
  for (int i = 2; i >= 0; i--) {
    if (ar_helper->bits[i] && loc_count < 2) {
      array->bits[++loc_count] = ar_helper->bits[i];
    }
  }
  if (sign) array->bits[3] |= 1 << 31;
  floating_point = floating_point << 16;
  array->bits[3] |= floating_point;
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

  generate_float(93, 234, 0, 7, num1, num1_helper);
  generate_float(93, 789, 0, 9, num2, num2_helper);
  convert_to_dec(&first, num1_helper, 0, 7, &ar_helper);
  convert_to_dec(&second, num2_helper, 0, 9, &ar_helper);
  int ret = s21_mul(first, second, &res);
  ck_assert_int_eq(ret, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(div_1) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(48, 234, 0, 7, num1, num1_helper);
  convert_to_dec(&first, num1_helper, 0, 7, &ar_helper);
  convert_to_dec(&second, num2_helper, 0, 0, &ar_helper);
  int ret = s21_div(first, second, &res);
  ck_assert_int_eq(ret, 3);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(div_2) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(50, 1234567, 1, 6, num1, num1_helper);
  generate_float(80, 1234, 0, 3, num2, num2_helper);
  convert_to_dec(&first, num1_helper, 1, 6, &ar_helper);
  convert_to_dec(&second, num2_helper, 0, 3, &ar_helper);
  mpf_div(num1, num1, num2);
  s21_div(first, second, &res);
  convert_to_mpf(res, s21_res);
  mpf_sub(num1, num1, s21_res);
  mpf_abs(num1, num1);
  ck_assert_int_eq(mpf_cmp_ui(num1, 2) < 0, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(fmod_1) {
  mpf_init(num1);
  mpf_init(num2);
  mpf_init(s21_res);
  mpz_init(num1_helper);
  mpz_init(num2_helper);

  generate_float(4, 1, 1, 1, num1, num1_helper);
  generate_float(6, 1, 0, 2, num2, num2_helper);
  convert_to_dec(&first, num1_helper, 1, 6, &ar_helper);
  convert_to_dec(&second, num2_helper, 0, 3, &ar_helper);
  s21_mod(first, second, &res);
  convert_to_mpf(res, s21_res);
  double fmodl_res = fmodl(-1.5, 0.63);
  mpf_set_d(num1, fmodl_res);
  mpf_sub(num1, num1, s21_res);
  mpf_abs(num1, num1);
  ck_assert_int_eq(mpf_cmp_ui(num1, 2) < 0, 1);

  clear_func(num1, num2, s21_res, num1_helper, num2_helper);
}
END_TEST

START_TEST(convertion_1) {
  float a = 0.00023456;
  float b;
  s21_decimal my_struct;
  s21_from_float_to_decimal(a, &my_struct);
  s21_from_decimal_to_float(my_struct, &b);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(convertion_2) {
  int a = 12345;
  int b;
  s21_decimal my_struct;
  s21_from_int_to_decimal(a, &my_struct);
  s21_from_decimal_to_int(my_struct, &b);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(is_not_eq) {
  s21_decimal a = {{1, 1, 1, 0}};
  s21_decimal b = {{1, 1, 1, 0}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, c), 1);
}
END_TEST

START_TEST(is_gr) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1, 1, 1, 0}}, c = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, c), 1);
}
END_TEST

START_TEST(is_gr_eq) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1, 1, 1, 0}}, c = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, c), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(c, a), 0);
}
END_TEST

START_TEST(is_le_eq) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1, 1, 1, 0}}, c = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, c), 0);
  ck_assert_int_eq(s21_is_less_or_equal(c, a), 1);
}
END_TEST

START_TEST(floor_t) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1844674407, 0, 0, 0}}, c = {{0, 0, 0, 0}};
  set_exponent(&a, 10);
  s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(floor_neg) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1844674408, 0, 0, 0}}, c = {{0, 0, 0, 0}};
  set_exponent(&a, 10);
  set_sign(&a, 1);
  set_sign(&b, 1);
  s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(round_t) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1844674408, 0, 0, 0}}, c = {{0, 0, 0, 0}};
  set_exponent(&a, 10);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(trunc_t) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1844674407, 0, 0, 0}}, c = {{0, 0, 0, 0}};
  set_exponent(&a, 10);
  s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(neg) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1, 1, 1, 0}}, c = {{0, 0, 0, 0}};
  set_exponent(&a, 10);
  set_exponent(&b, 10);
  set_sign(&b, 1);
  s21_negate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
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
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, fmod_1);
  tcase_add_test(tc1_1, convertion_1);
  tcase_add_test(tc1_1, convertion_2);

  tcase_add_test(tc1_1, is_not_eq);
  tcase_add_test(tc1_1, is_gr);
  tcase_add_test(tc1_1, is_gr_eq);
  tcase_add_test(tc1_1, is_le_eq);
  tcase_add_test(tc1_1, floor_t);
  tcase_add_test(tc1_1, floor_neg);
  tcase_add_test(tc1_1, round_t);
  tcase_add_test(tc1_1, trunc_t);
  tcase_add_test(tc1_1, neg);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
