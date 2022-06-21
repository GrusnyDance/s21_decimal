//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

int very_stupid_add(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result, int exp_1, int exp_2) {
  int res = OK;

  int additional_bit = 0;
  for (int i = 0; i < ALL_BIT; i++) {
    int a = get_bit(get_bits(value_1, i), i);
    int b = get_bit(get_bits(value_2, i), i);

    *p_get_bits(result, i) =
        set_bit(get_bits(*result, i), i, a ^ b ^ additional_bit);
    additional_bit = (a && b) || (b && additional_bit) || (a && additional_bit);
  }

  if (exp_1 && exp_2 && additional_bit) {
    bank_round(&value_1, 1);
    bank_round(&value_2, 1);
    res = very_stupid_add(value_1, value_2, result, get_exponent(value_1),
                          get_exponent(value_2));
  }
  elif (additional_bit) { res = BIG_VALUE; }

  return res;
}

int stupid_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = get_sign(value_1) == NEGATIVE;
  int sign_2 = get_sign(value_2) == NEGATIVE;

  int status;
  if (sign_1 && sign_2) {
    set_sign(&value_1, POSITIVE);
    set_sign(&value_2, POSITIVE);

    status = very_stupid_add(value_1, value_2, result, get_exponent(value_1),
                             get_exponent(value_2));

    set_sign(result, NEGATIVE);
  } else if (sign_1) {
    set_sign(&value_1, POSITIVE);
    status = s21_sub(value_2, value_1, result);
  } else if (sign_2) {
    set_sign(&value_2, POSITIVE);
    status = s21_sub(value_1, value_2, result);
  } else {
    status = very_stupid_add(value_1, value_2, result, get_exponent(value_1),
                             get_exponent(value_2));
  }

  return status;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  balancing(&value_1, &value_2);

  return stupid_add(value_1, value_2, result);
}
