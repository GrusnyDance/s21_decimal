//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

int get_exponent(s21_decimal a) {
    /// Get exponent in decimal [0 - 28]
    int sys_bit = (a.bits[DECIMAL_INFO] >> (BITS_IN_INT - END_EXP_BIT));

    int exp = 0;
    for (int i = (END_EXP_BIT - START_EXP_BIT); i >= 0; i--) {
        if (sys_bit & 1)
            exp += _2(i);
//        printf("bit - _%d_\n", sys_bit & 1);
        sys_bit >>= 1;
    }

    if (exp > 28)
        exp = 28;
    return exp;
}

int set_exponent(s21_decimal *a, int new_exponent) {
    /// Set exponent in decimal return 0
    for (int i = (BITS_IN_INT - START_EXP_BIT); i >= (BITS_IN_INT - END_EXP_BIT); i--) {
//        printf("new_bit - _%d_\n", new_exponent & 1);
        SET_BIT(a->bits[DECIMAL_INFO], i, new_exponent & 1);
        new_exponent >>= 1;
    }

    return 0;
}
