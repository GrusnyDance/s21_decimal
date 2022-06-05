//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

// int custom_less(s21_decimal value_1, s21_decimal value_2) {
//   int res = 0;
//   for (int i = ALL_BIT - 1; i >= 0; i--) {
//     if (get_gbit(value_1, i) == get_gbit(value_2, i))
//       continue;
//     else if (get_gbit(value_1, i) < get_gbit(value_2, i)) {
//       res = 1;
//       break;
//     } else
//       break;
//   }
//   return res;
// }

// int div_core(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
//              int res_exp) {
//   // result->bits[0] = INT32_MIN;
//   s21_decimal divcopy = value_2;
//   s21_decimal temp = {0, 0, 0, 0};
//   s21_decimal temp2 = {INT32_MIN, 0, 0, 0};
//   if (s21_is_equal(value_1, value_2)) {
//     return 0;
//   } else if (custom_less(value_1, value_2)) {
//     if (is_zero(value_1)) return 0;
//     // while (custom_less(value_1, value_2) && res_exp < 28) {
//     //   res_exp++;
//     //   s21_decimal ten = {(1 << 30) + (1 << 28), 0, 0, 0};
//     //   s21_mul(value_1, ten, &value_1);
//     //   s21_mul(*result, ten, result);
//     // }
//     return 0;
//   }

//   while (custom_less(value_2, value_1) || s21_is_equal(value_2, value_1)) {
//     right_shift(&value_2);
//     right_shift(result);
//   }
//   if (custom_less(value_1, value_2)) {
//     left_shift(&value_2);
//     left_shift(result);
//   }

//   d_print_decimal(value_1);
//   d_print_decimal(value_2);
//   printf("RES\n");
//   d_print_decimal(*result);
//   if (res_exp < 28) {
//     s21_sub(value_1, value_2, &temp);
//     // d_print_decimal(*result);
//     res_exp = div_core(temp, divcopy, &temp2, res_exp);
//     s21_add(*result, temp2, result);
//   }
//   //условие остановки для непереполнения
//   return res_exp;
// }

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   if (is_zero(value_2)) return DIV_ZERO;
//   result->bits[0] = INT32_MIN;
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