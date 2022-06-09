//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

s21_decimal div_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int res_exp, int *status) {
  s21_decimal divcopy = value_2;
  s21_decimal temp = {0, 0, 0, 0};
  s21_decimal temp2 = {INT32_MIN, 0, 0, 0};
  if (stupid_equal(value_1, value_2)) {
    return temp2;
  } else if (stupid_less(value_1, value_2)) {
    return temp;
  }
  while ((stupid_less(value_2, value_1) || stupid_equal(value_2, value_1)) &&
         !get_gbit(value_2, ALL_BIT - 1)) {
    // d_print_decimal(value_2);
    right_shift(&value_2);
    right_shift(result);
  }
  if (stupid_less(value_1, value_2)) {
    left_shift(&value_2);
    left_shift(result);
  }
  very_stupid_sub(value_1, value_2, &temp);
  temp2 = div_core(temp, divcopy, &temp2, res_exp, status);
  *status = very_stupid_add(*result, temp2, result);
  return *result;
}

int int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_zero(value_2)) return DIV_ZERO;
  int status = OK;
  result->bits[0] = INT32_MIN;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  int res_exp = get_exponent(value_1) - get_exponent(value_2);
  set_exponent(&value_1, 0);
  set_exponent(&value_2, 0);
  *result = div_core(value_1, value_2, result, res_exp, &status);
  if (res_exp > 28)
    bank_round(result, res_exp - 28);
  else if (res_exp < 29 && res_exp > 0)
    set_exponent(result, res_exp);
  else
    status = shifting(result, -res_exp);
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = int_div(value_1, value_2, result);
  s21_decimal mod_res, div_res, temp = *result;
  int exp = get_exponent(*result);
  s21_mod(value_1, value_2, &mod_res);
  shifting(&mod_res, -1);
  int_div(mod_res, value_2, &div_res);
  // set_exponent(&div_res, get_exponent(div_res) - 1);
  // d_print_decimal(div_res);
  s21_add(*result, div_res, result);
  return status;
}