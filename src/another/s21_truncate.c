#include "decimal_another.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;

  s21_decimal one, mod_res;
  s21_from_int_to_decimal(1, &one);

  s21_mod(*result, one, &mod_res);
  // d_print_decimal(mod_res);
  // d_print_decimal(*result);

  balancing(&mod_res, result);

  very_stupid_sub(*result, mod_res, result);

  bank_round(result, get_exponent(*result));

  set_sign(result, get_sign(value));
  return OK;
}
