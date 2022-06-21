#include "decimal_another.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal one, zeroDotFive, mod_res;

  s21_from_int_to_decimal(1, &one);
  s21_from_int_to_decimal(5, &zeroDotFive);
  set_exponent(&zeroDotFive, 1);

  s21_mod(value, one, &mod_res);
  set_sign(&mod_res, 0);

  s21_truncate(value, result);
  if (!s21_is_less(mod_res, zeroDotFive))
    very_stupid_add(*result, one, result, 0, 0);
  return OK;
}
