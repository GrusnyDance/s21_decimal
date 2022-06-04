//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    s21_decimal a = {(1 << 30), 0, 0, 0};
    s21_decimal b = {~(INT32_MAX - (1 << 29)), 0, 0, 0};
    s21_decimal c = {0, 0, 0, 0};
    print_decimal(a);
    print_decimal(b);
    s21_mul(a, b, &c);
    print_decimal(c);
}
