#include <check.h>

#include "s21_decimal.h"

START_TEST(is_not_eq) {
  s21_decimal a = {1, 1, 1, 0}, b = {1, 1, 1, 0}, c = {0, 0, 0, 0};
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, c), 1);
}
END_TEST

START_TEST(is_gr) {
  s21_decimal a = {1, 1, 1, 0}, b = {1, 1, 1, 0}, c = {0, 0, 0, 0};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, c), 1);
}
END_TEST

START_TEST(is_gr_eq) {
  s21_decimal a = {1, 1, 1, 0}, b = {1, 1, 1, 0}, c = {0, 0, 0, 0};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, c), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(c, a), 0);
}
END_TEST

START_TEST(is_le_eq) {
  s21_decimal a = {1, 1, 1, 0}, b = {1, 1, 1, 0}, c = {0, 0, 0, 0};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, c), 0);
  ck_assert_int_eq(s21_is_less_or_equal(c, a), 1);
}
END_TEST

START_TEST(floor) {
  s21_decimal a = {1, 1, 1, 0}, b = {1844674407, 0, 0, 0}, c = {0, 0, 0, 0};
  set_exponent(&a, 10);
  s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(floor_neg) {
  s21_decimal a = {1, 1, 1, 0}, b = {1844674408, 0, 0, 0}, c = {0, 0, 0, 0};
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

START_TEST(round) {
  s21_decimal a = {1, 1, 1, 0}, b = {1844674408, 0, 0, 0}, c = {0, 0, 0, 0};
  set_exponent(&a, 10);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(trunc) {
  s21_decimal a = {1, 1, 1, 0}, b = {1844674407, 0, 0, 0}, c = {0, 0, 0, 0};
  set_exponent(&a, 10);
  s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}
END_TEST

START_TEST(neg) {
  s21_decimal a = {1, 1, 1, 0}, b = {1, 1, 1, 0}, c = {0, 0, 0, 0};
  set_exponent(&a, 10);
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

  tcase_add_test(tc1_1, is_not_eq);
  tcase_add_test(tc1_1, is_gr);
  tcase_add_test(tc1_1, is_gr_eq);
  tcase_add_test(tc1_1, is_le_eq);
  tcase_add_test(tc1_1, floor);
  tcase_add_test(tc1_1, floor_neg);
  tcase_add_test(tc1_1, round);
  tcase_add_test(tc1_1, trunc);
  tcase_add_test(tc1_1, neg);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
