//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

sign get_sign(s21_decimal a) {
    /// Return 0 if a is positive else return not zero
    return get_bit(a.bits[DECIMAL_INFO], SIGN_BIT);
}

int set_sign(s21_decimal *a, sign new_sign) {
    /// Return 0
    a->bits[DECIMAL_INFO] = set_bit(a->bits[DECIMAL_INFO], SIGN_BIT, new_sign);
    return 0;
}

