//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef SRC_ARITHMETIC_DECIMAL_ARITHMETIC_H_
#define SRC_ARITHMETIC_DECIMAL_ARITHMETIC_H_

#include "../another/decimal_another.h"
#include "../comparison/decimal_comparison.h"
#include "../convertion/decimal.h"
#include "../core/decimal_core.h"

// ADD
int very_stupid_add(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result, int exp_1, int exp_2);
int stupid_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int very_stupid_sub(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int stupid_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int stupid_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif  // SRC_ARITHMETIC_DECIMAL_ARITHMETIC_H_
