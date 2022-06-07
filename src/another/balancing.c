//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_another.h"



int shifting(s21_decimal *a, int n) {
    /// Number shift by 10
    s21_decimal bobka = {(1 << 30) + (1 << 28), 0, 0, 0};
    int exp = get_exponent(*a);

    int status = s21_mul(*a, bobka, a);
    while (n-- && exp < MAX_EXPONENT && !status) {
        exp++;
        status = s21_mul(*a, bobka, a);
    }
    set_exponent(a, exp);
    return status;
}


int balancing(s21_decimal *a, s21_decimal *b) {
    int status = 0;

    int exp_a = get_exponent(*a);
    int exp_b = get_exponent(*b);

    if (exp_a != exp_b) {
        shifting(a, -1);
        shifting(b, -1);

//    if (exp_a > exp_b) {
////        ba
//    } else {
//
//    }
    }
    return status;
}
