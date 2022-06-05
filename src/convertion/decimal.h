#ifndef DECIMAL_H_
#define DECIMAL_H_

#include <math.h>

#include "../core/decimal_core.h"

#define CONVERTION_ERROR 1
#define OK 0

// typedef struct
// {
//     int bits[4];
// } s21_decimal;

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
void change_endian(s21_decimal *my_struct);
void set_sign2(s21_decimal *my_struct);
void set_null(s21_decimal *my_struct);

#endif
