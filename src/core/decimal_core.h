//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef S21_DECIMAL_DECIMAL_CORE_H
#define S21_DECIMAL_DECIMAL_CORE_H

#include "MyLib/style.h"
#include "MyLib/bit.h"

#define _2(i) (1 << i)

#define DECIMAL_INFO 3
#define SIGN_BIT 31
#define START_EXP_BIT 16
#define END_EXP_BIT 23

typedef struct {
    int bits[4];
} s21_decimal;

int get_sign(s21_decimal a);
int set_sign(s21_decimal *a, int new_sign);

// Work with exponent
int get_exponent(s21_decimal a);
int set_exponent(s21_decimal *a, int new_exponent);

int shift_left(s21_decimal *a);


#endif //S21_DECIMAL_DECIMAL_CORE_H
