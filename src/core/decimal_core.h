//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef S21_DECIMAL_DECIMAL_CORE_H
#define S21_DECIMAL_DECIMAL_CORE_H

#include "MyLib/style.h"
#include "constants.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define _2(bit) (1 << (BITS_IN_INT - bit - 1))

typedef enum {
    POSITIVE,
    NEGATIVE
} sign;

typedef struct {
    int bits[4];
} s21_decimal;

sign get_sign(s21_decimal a);
int set_sign(s21_decimal *a, sign new_sign);

// Work with exponent
int get_exponent(s21_decimal a);
int set_exponent(s21_decimal *a, int new_exponent);

int shift_left(s21_decimal *a);

void print_decimal(s21_decimal a);

// Work with bit
int on_bit(int bits, int bit);
int off_bit(int bits, int bit);
int is_bit(int bits, int bit);
int get_bit(int bits, int bit);
int get_gbit(s21_decimal a, int gbit);
int set_bit(int bits, int bit, int new_bit);
int get_bits(s21_decimal a, int global_ind);
int* p_get_bits(s21_decimal *a, int global_ind);
char* decimal2str(s21_decimal a);

#endif //S21_DECIMAL_DECIMAL_CORE_H
