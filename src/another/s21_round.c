#include "decimal_another.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal zeroDotFive = {{5, 0, 0, 0}}, mod_res, one = {{1, 0, 0, 0}};
  s21_mod(value, one, &mod_res);
  s21_truncate(value, result);
  set_exponent(&zeroDotFive, 1);
  set_sign(&mod_res, 0);
  if (!s21_is_less(mod_res, zeroDotFive))
    very_stupid_add(*result, one, result, 0, 0);
  return 0;
}