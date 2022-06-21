//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_another.h"

int shifting(s21_decimal *a, int n) {
  /// Multiply the number by 1 and increase the exponent by 1 thereby shifting
  /// the number to the left
  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);

  s21_decimal tmp_result = init_zero_decimal();

  int exp = get_exponent(*a);
  int status = exp == MAX_EXPONENT;

  while (!status && n--) {
    status = stupid_mul(*a, ten, &tmp_result);
    if (!status) {
      *a = tmp_result;
      status = (++exp == MAX_EXPONENT);
    }
  }

  set_exponent(a, exp);
  return status;
}

int balancing(s21_decimal *a, s21_decimal *b) {
  int diff = get_exponent(*a) - get_exponent(*b);

  if (diff) {
    if (diff > 0)
      shifting(b, diff);
    else
      shifting(a, -diff);

    diff = get_exponent(*a) - get_exponent(*b);
    if (diff) {
      if (diff > 0)
        bank_round(a, diff);
      else
        bank_round(b, -diff);
    }
  }

  return OK;
}
