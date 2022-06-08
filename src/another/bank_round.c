#include "decimal_another.h"

int bank_rounding(int a) {
  int res = 0;
  if (a % 10 > 5 || (a % 10 == 5 && a / 10 % 2)) res = 1;
  return res;
}

int bank_round(s21_decimal *a, int n) {
  while (n--) {
    s21_decimal mod_res, ten, hun;
    s21_from_int_to_decimal(100, &hun);
    s21_from_int_to_decimal(10, &ten);
    stupid_mod(*a, hun, &mod_res);
    // d_print_decimal(*a);
    change_endian(&mod_res);
    int mask = 127 & mod_res.bits[0];
    s21_div(*a, ten, a);
    int exp = get_exponent(*a) - 1;
    set_exponent(a, exp);
    if (bank_rounding(mask)) {
      s21_decimal one = {INT32_MIN, 0, 0, 0};
      very_stupid_add(*a, one, a);
    }
  }
  return 0;
}
