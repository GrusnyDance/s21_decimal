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
  if (exp_1 > 0 && exp_2 > 0 && additional_bit) {
    bank_round(&value_1, 1);
    bank_round(&value_2, 1);
    res = very_stupid_add(value_1, value_2, result, get_exponent(value_1),
                          get_exponent(value_2));
  } else if (additional_bit)
    res = BIG_VALUE;

  // if (additional_bit) {
  //   res = BIG_VALUE;
  // }

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
  }
  elif (sign_1) {
    set_sign(&value_1, POSITIVE);
    status = s21_sub(value_2, value_1, result);
  }
  elif (sign_2) {
    set_sign(&value_2, POSITIVE);
    status = s21_sub(value_1, value_2, result);
  }
  else {
    status = very_stupid_add(value_1, value_2, result, get_exponent(value_1),
                             get_exponent(value_2));
  }
  return status;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // print_decimal(value_1);
  // print_decimal(value_2);
  // printf("BALANING\n");
  *result = init_zero_decimal();
  // d_print_decimal(value_1);
  // d_print_decimal(value_2);
  balancing(&value_1, &value_2);
  // d_print_decimal(value_1);
  // d_print_decimal(value_2);

  // print_decimal(value_1);
  // print_decimal(value_2);
  // d_print_decimal(value_1);
  // d_print_decimal(value_2);

  int exp = get_exponent(value_1);
  set_exponent(result, exp);
  int result_add = stupid_add(value_1, value_2, result);

  // IF I can shift and need shift
  if (result_add) {
    // (Get result % 10 + (2^97 % 10) % 10)) % 10 i get last number
    // i div result on 10 and +1 if need bank round
    // s21_mod(value_1, value_2, )
  }
  // print_decimal(*result);
  return result_add;
}
