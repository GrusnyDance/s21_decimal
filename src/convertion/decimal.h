#ifndef SRC_CONVERTION_DECIMAL_H_
#define SRC_CONVERTION_DECIMAL_H_

#include <math.h>

#include "../core/decimal_core.h"
#include "../arithmetic/decimal_arithmetic.h"

// typedef struct
// {
//     int bits[4];
// } s21_decimal;

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
void change_endian(s21_decimal *my_struct);
void set_null(s21_decimal *my_struct);

#endif  // SRC_CONVERTION_DECIMAL_H_
