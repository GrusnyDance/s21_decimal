//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    s21_decimal a = {9, 0, 0, 0};
    s21_decimal b = {10000, 0, 0, 0};
    set_sign(&a, NEGATIVE);
    s21_decimal c = {0, 0, 0, 0};
    print_decimal(a);
    s21_sub(a, b, &c);
    print_decimal(a);
    print_decimal(b);
    print_decimal(c);
//    for (int i = 0; i < 75; i++) {
//        s21_add(a, a, &a);
//        print_decimal(a);
//    }
//    set_sign(&a, 10);
//    print_decimal(a);
//    set_sign(&a, 0);
//    print_decimal(a);
//    printf("%d\n", get_exponent(a));
//    set_exponent(&a, 1);
//    printf("%d\n", get_exponent(a));
//    print_decimal(a);
//    set_exponent(&a, 10);
//    printf("%d\n", get_exponent(a));
//    print_decimal(a);
//    set_exponent(&a, -10);
//    printf("%d\n", get_exponent(a));
//    print_decimal(a);
//
//    set_exponent(&a, 30);
//    printf("%d\n", get_exponent(a));
//    print_decimal(a);

}
