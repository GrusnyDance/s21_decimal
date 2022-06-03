//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

int get_exponent(s21_decimal a) {
    /// Get exponent in decimal [0 - 28]
    int sys_bit = (a.bits[DECIMAL_INFO] >> START_EXP_BIT);

    int exp = 0;
    for (int i = 0; i < (END_EXP_BIT - START_EXP_BIT); i++) {
        if (sys_bit & 1)
            exp += _2(i);
        sys_bit >>= 1;
    }

    if (exp > 28)
        exp = 28;
    return exp;
}

int set_exponent(s21_decimal *a, int new_exponent) {
    /// Set exponent in decimal return 0
    for (int i = START_EXP_BIT; i <= END_EXP_BIT; i++) {
        SET_BIT(a->bits[DECIMAL_INFO], i, new_exponent & 1);
        new_exponent >>= 1;
    }

    return 0;
}
