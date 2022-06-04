//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_arithmetic.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    balancing(&value_1, &value_2);

    int status = 0;

    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);

    if (sign_1 && sign_2) {
        set_sign(&value_1, POSITIVE);
        set_sign(&value_2, POSITIVE);
        status = s21_add(value_1, value_2, result);
        set_sign(result, NEGATIVE);
    } elif (sign_1) {
        status = s21_sub(value_2, value_1, result);
    } elif (sign_2) {
        set_sign(&value_2, POSITIVE);
        status = s21_sub(value_1, value_2, result);
    } else {
        int n = 0;
        for (int i = 0; i < ALL_BIT; i++) {
            int a = get_bit(get_bits(value_1, i), i);
            int b = get_bit(get_bits(value_2, i), i);

            *p_get_bits(result, i) = set_bit(get_bits(*result, i), i,a ^ b ^ n);
            n = (a && b) || (b && n) || (a && n);
            // TODO add shift
        }
        if (n)
            status = BIG_VALUE;
    }

    return status;
}
