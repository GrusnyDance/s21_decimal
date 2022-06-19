#include "decimal_another.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one = {1, 0, 0, 0}, mod_res;
  s21_mod(value, one, &mod_res);
  if (get_sign(value) && !is_zero(value) && !is_zero(mod_res)) {
    s21_truncate(value, result);
    very_stupid_add(*result, one, result, 0, 0);
  } else
    s21_truncate(value, result);
  return 0;
}