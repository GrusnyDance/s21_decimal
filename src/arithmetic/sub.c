//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

int very_stupid_sub(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  int status = 0;
  for (int i = 0; i < ALL_BIT; i++) {
    if (get_gbit(value_2, i) && !get_gbit(value_1, i)) {
      int j;
      for (j = i + 1; !get_gbit(value_1, j) && j < ALL_BIT;) {
        j++;
      }
      *p_get_bits(&value_1, j) = set_bit(get_bits(value_1, j), j, 0);
      for (j--; j != i; j--) {
        *p_get_bits(&value_1, j) = set_bit(get_bits(value_1, j), j, 1);
      }
      *p_get_bits(result, i) = set_bit(get_bits(*result, i), i, 1);
    } else {
      int a = get_gbit(value_1, i);
      int b = get_gbit(value_2, i);
      *p_get_bits(result, i) = set_bit(get_bits(*result, i), i, a ^ b);
    }
    // TODO left shift
  }
  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  balancing(&value_1, &value_2);
  int exp_a = get_exponent(value_1);
  int exp_b = get_exponent(value_2);
  int exp = (exp_a < exp_b) ? exp_a : exp_b;
  set_exponent(result, exp);
  d_print_decimal(value_1);
  d_print_decimal(value_2);

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  int status = 0;
  if (sign_1 && sign_2) {
    status = stupid_add(value_2, value_1, result);
  }
  elif (sign_1) {
    set_sign(&value_2, NEGATIVE);
    status = stupid_add(value_1, value_2, result);
  }
  elif (sign_2) { status = stupid_add(value_1, value_2, result); }
  elif (s21_is_less(value_1, value_2)) {
    status = very_stupid_sub(value_2, value_1, result);
    set_sign(result, NEGATIVE);
  }
  else {
    // printf("asdaasfa");
    very_stupid_sub(value_1, value_2, result);
  }
  return status;
}
