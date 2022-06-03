//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

int get_sign(s21_decimal a) {
    /// Return 0 if a is positive else return not zero
    return GET_BIT(a.bits[DECIMAL_INFO], SIGN_BIT);
}

int set_sign(s21_decimal *a, int new_sign) {
    /// Return 0
    SET_BIT(a->bits[DECIMAL_INFO], SIGN_BIT, new_sign);
    return 0;
}

