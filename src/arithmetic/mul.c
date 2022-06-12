//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_arithmetic.h"

int stupid_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    *result = init_zero_decimal();

    int status = 0;
    s21_decimal tmp = *result;
    set_sign(&tmp, get_sign(value_1) ^ get_sign(value_2));
    while (!is_zero(value_2)) {
        if (get_gbit(value_2, 0)) {
          status = very_stupid_add(value_1, tmp, &tmp);
          if (status) break;
        }
        right_shift(&value_1);
        left_shift(&value_2);
    }

    if (!status)
      *result = tmp;
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exp = get_exponent(value_1) + get_exponent(value_2);
  int res = stupid_mul(value_1, value_2, result);
  if (exp < 29 && exp >= 0)
    set_exponent(result, exp);
  else
    bank_round(result, exp - 28);
  return res;
}
