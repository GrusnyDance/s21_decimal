#include "decimal_another.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;
  s21_decimal mod_res, one = {INT32_MIN, 0, 0, 0};
  s21_mod(*result, one, &mod_res);
  balancing(&mod_res, result);
  very_stupid_sub(*result, mod_res, result);
  bank_round(result, get_exponent(*result));
  set_sign(result, get_sign(value));
  // while (!get_gbit(*result, 0)) left_shift(result);
  return 0;
}
