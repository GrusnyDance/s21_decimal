#include "decimal_another.h"

int bank_rounding(int a) {
    /// returns 1 if you need to apply bank rounding or 0 if not
    return (a % 10 > 5 || (a % 10 == 5 && (a / 10) % 2));
}

int bank_round(s21_decimal *number, int n) {
    s21_decimal one, ten, hund;
    s21_from_int_to_decimal(1, &one);
    s21_from_int_to_decimal(10, &ten);
    s21_from_int_to_decimal(100, &hund);

  while (n--) {
    s21_decimal mod_res = init_zero_decimal();
    stupid_mod(*number, hund, &mod_res);

    int exp = get_exponent(*number) - 1;
    int_div(*number, ten, number);
    set_exponent(number, exp);

    if (bank_rounding(mod_res.bits[0])) {
      very_stupid_add(*number, one, number, 0, 0);
    }
  }

  return 0;
}
