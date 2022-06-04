//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    s21_decimal a = {19, 0, 0, 0};
    set_exponent(&a, 1);
    s21_decimal b = {95, 0, 0, 0};
    set_exponent(&b, 2);
    s21_decimal c = {0, 0, 0, 0};
    print_decimal(a);
    print_decimal(b);
    printf("is eq = %d\n", s21_is_equal(a, b));
}
