//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_arithmetic.h"

int stupid_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // *result = init_zero_decimal();

  int status = 0;
  s21_decimal tmp = *result;
  set_sign(&tmp, get_sign(value_1) ^ get_sign(value_2));

  while (!is_zero(value_2) && !status) {
    if (get_gbit(value_2, 0)) {
      status = very_stupid_add(tmp, value_1, &tmp, 0, 0);
    }
    if (get_gbit(value_1, ALL_BIT - 1)) status = 1;
    right_shift(&value_2);
    left_shift(&value_1);
  }

  if (!status)
    *result = tmp;
  else if (get_sign(value_1) ^ get_sign(value_2))
    ++status;
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = init_zero_decimal();
  int res = stupid_mul(value_1, value_2, result);
  while (res && (get_exponent(value_1) || get_exponent(value_2))) {
    int exp_check = stupid_less(value_1, value_2) ? get_exponent(value_2)
                                                  : get_exponent(value_1);
    s21_decimal *value = stupid_less(value_1, value_2) ? &value_2 : &value_1;
    s21_decimal *alt_value =
        !stupid_less(value_1, value_2) ? &value_2 : &value_1;
    if (exp_check)
      bank_round(value, 1);
    else
      bank_round(alt_value, 1);
    res = stupid_mul(value_1, value_2, result);
  }
  int exp = get_exponent(value_1) + get_exponent(value_2);
  if (exp < 29)
    set_exponent(result, exp);
  else
    *result = init_zero_decimal();
  return res;
}
