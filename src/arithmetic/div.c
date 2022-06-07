//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

s21_decimal div_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int res_exp) {
  // result->bits[0] = INT32_MIN;
  // static s21_decimal result = {INT32_MIN, 0, 0, 0};
  s21_decimal divcopy = value_2;
  s21_decimal temp = {0, 0, 0, 0};
  s21_decimal temp2 = {INT32_MIN, 0, 0, 0};
  if (stupid_equal(value_1, value_2)) {
    return temp2;
  } else if (stupid_less(value_1, value_2)) {
    // if (is_zero(value_1)) return 0;
    return temp;
    // while (stupid_less(value_1, value_2) && res_exp < 28) {
    //   if (is_zero(value_1)) return 0;
    //   res_exp++;
    //   s21_decimal ten = {(1 << 30) + (1 << 28), 0, 0, 0};
    //   s21_mul(value_1, ten, &value_1);
    //   s21_mul(*result, ten, result);
    // }
  }
  while (stupid_less(value_2, value_1) || stupid_equal(value_2, value_1)) {
    right_shift(&value_2);
    right_shift(result);
  }
  if (stupid_less(value_1, value_2)) {
    left_shift(&value_2);
    left_shift(result);
  }

  // d_print_decimal(value_1);
  // d_print_decimal(value_2);
  // printf("RES\n");
  // d_print_decimal(*result);
  very_stupid_sub(value_1, value_2, &temp);
  // d_print_decimal(*result);
  temp2 = div_core(temp, divcopy, &temp2, res_exp);
  very_stupid_add(*result, temp2, result);
  // d_print_decimal(*result);

  //условие остановки для непереполнения
  return *result;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_zero(value_2)) return DIV_ZERO;
  result->bits[0] = INT32_MIN;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  int res_exp = get_exponent(value_1) - get_exponent(value_2);
  // set_exponent(&value_1, 0);
  // set_exponent(&value_2, 0);
  *result = div_core(value_1, value_2, result, res_exp);
  set_exponent(result, res_exp);
  // printf("%d\n", get_exponent(*result));
  return 0;
}

// int div_core(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
//              int res_exp) {
//   result->bits[0] = INT32_MIN;
//   s21_decimal temp = {0, 0, 0, 0};
//   if (stupid_equal(value_1, value_2)) {
//     return 0;
//   }
//   print_decimal(*result);
//   while (s21_is_less(value_1, value_2) && res_exp < 28) {
//     res_exp++;
//     s21_decimal ten = {(1 << 30) + (1 << 28), 0, 0, 0};
//     s21_mul(value_1, ten, &value_1);
//   }
//   while (s21_is_less(value_2, value_1) || stupid_equal(value_2, value_1)) {
//     right_shift(&value_2);
//     right_shift(result);
//   }
//   if (s21_is_less(value_1, value_2)) {
//     left_shift(&value_2);
//     left_shift(result);
//   }
//   s21_sub(value_1, value_2, &temp);
//   if (res_exp < 28) res_exp = div_core(temp, value_2, &temp, res_exp);
//   s21_add(*result, temp, result);
//   //условие остановки для непереполнения
//   return res_exp;
// }

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
// {
//   if (is_zero(value_2)) return DIV_ZERO;
//   result->bits[0] = 0;
//   result->bits[1] = 0;
//   result->bits[2] = 0;
//   result->bits[3] = 0;
//   set_sign(result, get_sign(value_1) ^ get_sign(value_2));
//   set_sign(&value_1, 0);
//   set_sign(&value_2, 0);
//   int res_exp = get_exponent(value_1) - get_exponent(value_2);
//   set_exponent(&value_1, 0);
//   set_exponent(&value_2, 0);
//   res_exp = div_core(value_1, value_2, result, res_exp);
//   set_exponent(result, res_exp);
//   return 0;
// }
