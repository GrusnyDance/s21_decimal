//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

int get_exponent(s21_decimal a) {
    /// Get exponent in decimal [0 - 28]
    int exp = 0;
    for (int i = START_EXP_BIT; i <= END_EXP_BIT; i++) {
        if (is_bit(a.bits[DECIMAL_INFO], i))
            exp += (1 << (i - START_EXP_BIT));
    }

    if (exp > MAX_EXPONENT)
        exp = MAX_EXPONENT;
    return exp;
}

int set_exponent(s21_decimal *a, int new_exponent) {
    /// Set exponent in decimal return 0
    for (int i = START_EXP_BIT; i <= END_EXP_BIT; i++) {
        a->bits[DECIMAL_INFO] = set_bit(a->bits[DECIMAL_INFO], i, new_exponent & 1);
        new_exponent >>= 1;
    }

    return 0;
}
