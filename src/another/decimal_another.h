//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef S21_DECIMAL_DECIMAL_ANOTHER_H
#define S21_DECIMAL_DECIMAL_ANOTHER_H

#include "../MyLib/style.h"
#include "../core/decimal_core.h"


int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// custom
int balancing(s21_decimal *a, s21_decimal *b);


#endif //S21_DECIMAL_DECIMAL_ANOTHER_H
