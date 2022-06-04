//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_another.h"

int shifting(s21_decimal *a) {
    int status = 0;
    s21_decimal bobka = {(1 << 30) + (1 << 28), 0, 0, 0};
    int exp = get_exponent(*a);
    while (exp < 28 && !(status = s21_mul(*a, bobka, a))) {
        exp += 1;
    }
    set_exponent(a, exp);
    return status;
}


int balancing(s21_decimal *a, s21_decimal *b) {
    int status = 0;

    if (get_exponent(*a) != get_exponent(*b)) {

        shifting(a);
        shifting(b);

        int exp_a = get_exponent(*a);
        int exp_b = get_exponent(*b);
//    if (exp_a > exp_b) {
////        ba
//    } else {
//
//    }
    }
    return status;
}
