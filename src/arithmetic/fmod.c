#include "decimal_arithmetic.h"

int custom_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = ALL_BIT - 1; i >= 0; i--) {
    if (get_gbit(value_1, i) == get_gbit(value_2, i))
      continue;
    else if (get_gbit(value_1, i) < get_gbit(value_2, i)) {
      res = 1;
      break;
    } else
      break;
  }
  return res;
}

s21_decimal fmod_core(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal* divided) {
  s21_decimal divcopy = value_2;
  s21_decimal res = {0, 0, 0, 0};
  s21_decimal temp = {0, 0, 0, 0};
  print_decimal(*divided);
  if (s21_is_equal(value_1, value_2))
    return res;
  else if (custom_less(value_1, value_2))
    return value_1;

  while (custom_less(value_2, value_1) || s21_is_equal(value_2, value_1)) {
    right_shift(&value_2);
    right_shift(divided);
  }
  if (custom_less(value_1, value_2)) {
    left_shift(&value_2);
    left_shift(divided);
  }

  s21_sub(value_1, value_2, &temp);
  res = fmod_core(temp, divcopy, divided);
  return res;
}

int stupid_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (is_zero(value_2)) return DIV_ZERO;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  s21_decimal divided;
  s21_from_int_to_decimal(1, &divided);
  set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  int res_exp = get_exponent(value_2);
  set_exponent(&value_1, 0);
  set_exponent(&value_2, 0);
  *result = fmod_core(value_1, value_2, &divided);
  set_exponent(result, res_exp);
  return 0;
}