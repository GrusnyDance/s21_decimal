#include <math.h>
#include <stdio.h>
#include "decimal.h"

int main() {
    float a = 0.00023456;
    float b;
    s21_decimal my_struct;
    s21_from_float_to_decimal(a, &my_struct);
    s21_from_decimal_to_float(my_struct, &b);
    printf("%f\n", a);
    printf("%f\n", b);
}