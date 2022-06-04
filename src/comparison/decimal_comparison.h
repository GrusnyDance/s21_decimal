//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef S21_DECIMAL_DECIMAL_COMPARISON_H
#define S21_DECIMAL_DECIMAL_COMPARISON_H


#include "../core/decimal_core.h"
#include "../another/decimal_another.h"

typedef enum {
    false,
    true
} bool;


int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);


#endif //S21_DECIMAL_DECIMAL_COMPARISON_H
