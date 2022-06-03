//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    s21_decimal a = {1 << 31, 1 << 31, 1 << 31, (1 << 31)};
    printf("%d\n", get_sign(a));
    set_sign(&a, 0);
    printf("%d\n", get_sign(a));
    set_sign(&a, 10);
    printf("%d\n", get_sign(a));
    set_sign(&a, 0);
    printf("%d\n", get_sign(a));
}