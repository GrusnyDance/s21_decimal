//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

int very_stupid_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;

  int additional_bit = 0;
  for (int i = 0; i < ALL_BIT; i++) {
    int a = get_bit(get_bits(value_1, i), i);
    int b = get_bit(get_bits(value_2, i), i);

    *p_get_bits(result, i) = set_bit(get_bits(*result, i), i, a ^ b ^ additional_bit);
    additional_bit = (a && b) || (b && additional_bit) || (a && additional_bit);

    // TODO add shift
  }

    if (additional_bit) {
      res = BIG_VALUE;
  }

  return res;
}

int stupid_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);

    int status;
    if (sign_1 == NEGATIVE && sign_2 == NEGATIVE) {
        set_sign(&value_1, POSITIVE);
        set_sign(&value_2, POSITIVE);

        status = very_stupid_add(value_1, value_2, result);

        set_sign(result, NEGATIVE);
    } elif (sign_1 == NEGATIVE) {
        status = s21_sub(value_2, value_1, result);
    } elif (sign_2 == NEGATIVE) {
        set_sign(&value_2, POSITIVE);
        status = very_stupid_add(value_1, value_2, result);
    } else {
        status = very_stupid_add(value_1, value_2, result);
    }
    return status;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    balancing(&value_1, &value_2);
    return stupid_add(value_1, value_2, result);
}
