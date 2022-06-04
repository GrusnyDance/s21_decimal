//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_arithmetic.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  set_sign(result, get_sign(value_1) ^ get_sign(value_2));

  int status = 0;

  s21_decimal tmp = *result;
  while (!is_zero(value_2)) {
    if (get_gbit(value_2, 0)) {
      status = s21_add(value_1, tmp, &tmp);
      if (status) break;
    }
    right_shift(&value_1);
    left_shift(&value_2);

    right_shift(&value_1);
    left_shift(&value_2);
  }

  if (!status) *result = tmp;

  return status;
}
