//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    s21_decimal a = {1 << 31, 1 << 31, 1 << 31, (1 << 16)};
    printf("%d\n", get_exponent(a));
    set_exponent(&a, 10);
    set_exponent(&a, 27);
    printf("%d\n", get_exponent(a));
}