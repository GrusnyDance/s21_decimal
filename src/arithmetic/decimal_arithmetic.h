//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef S21_DECIMAL_DECIMAL_ARITHMETIC_H
#define S21_DECIMAL_DECIMAL_ARITHMETIC_H

#include "../another/decimal_another.h"
#include "../comparison/decimal_comparison.h"
#include "../convertion/decimal.h"
#include "../core/decimal_core.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif  // S21_DECIMAL_DECIMAL_ARITHMETIC_H
