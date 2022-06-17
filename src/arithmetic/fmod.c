#include "decimal_arithmetic.h"

s21_decimal fmod_core(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal divcopy = value_2;
  s21_decimal res;
  s21_decimal temp = {0, 0, 0, 0};
  // print_decimal(*divided);
  if (stupid_equal(value_1, value_2))
    return temp;
  else if (stupid_less(value_1, value_2))
    return value_1;

  while ((stupid_less(value_2, value_1) || stupid_equal(value_2, value_1)) &&
         !get_gbit(value_2, ALL_BIT - 1)) {
    left_shift(&value_2);
    // if (get_gbit(*divided, ALL_BIT - 1)) bank_round(divided, 1);
    // right_shift(divided);
  }
  if (stupid_less(value_1, value_2)) {
    // d_print_decimal(value_2);
    right_shift(&value_2);
    // d_print_decimal(value_2);
    // left_shift(divided);
  }
  very_stupid_sub(value_1, value_2, &temp);
  // d_print_decimal(temp);
  res = fmod_core(temp, divcopy);
  return res;
}

int stupid_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (is_zero(value_2)) return DIV_ZERO;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  // result->bits[3] = 0;
  // s21_decimal divided;
  // s21_from_int_to_decimal(1, &divided);
  set_sign(result, get_sign(value_1));
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  // int res_exp = get_exponent(value_1);
  // set_exponent(&value_1, 0);
  // set_exponent(&value_2, 0);
  *result = fmod_core(value_1, value_2);
  // set_exponent(result, res_exp);
  return 0;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  balancing(&value_1, &value_2);
  // d_print_decimal(value_1);
  // d_print_decimal(value_2);
  int exp = get_exponent(value_1);
  int res = stupid_mod(value_1, value_2, result);
  set_exponent(result, exp);
  return res;
}