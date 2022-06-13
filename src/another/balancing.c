//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_another.h"

int shifting(s21_decimal *a, int n) {
  /// Number shift by 10
  s21_decimal bobka = {10, 0, 0, 0};
  s21_decimal tmp = *a;
  int exp = get_exponent(*a);

  int status = exp == MAX_EXPONENT;
  // if (!status) {
  //   exp++;
  //   *a = tmp;
  // }
  while (n-- && exp < MAX_EXPONENT && !status) {
    status = stupid_mul(tmp, bobka, &tmp);
    // d_print_decimal(tmp);
    if (!status) {
      *a = tmp;
      exp++;
    }
  }
  set_exponent(a, exp);
  return status;
}

int balancing(s21_decimal *a, s21_decimal *b) {
  int status = 0;
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
  return status;
}
