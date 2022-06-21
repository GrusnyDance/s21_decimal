//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef SRC_ANOTHER_DECIMAL_ANOTHER_H_
#define SRC_ANOTHER_DECIMAL_ANOTHER_H_

#include <stdint.h>

#include "../MyLib/style.h"
#include "../arithmetic/decimal_arithmetic.h"
#include "../core/decimal_core.h"

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// custom
int balancing(s21_decimal *a, s21_decimal *b);
int bank_round(s21_decimal *a, int n);
int shifting(s21_decimal *a, int n);

#endif  // SRC_ANOTHER_DECIMAL_ANOTHER_H_
