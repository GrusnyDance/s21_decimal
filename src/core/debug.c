//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_core.h"

void print_decimal(s21_decimal a) {
    /// Print Decimal

    putchar(':');
    for (int i = 0; i < ALL_BIT; i++) {
        if (!(i % 32))
            putchar('-');
        putchar('0' + get_bit(get_bits(a, i), i));
    }

    putchar(':');
    for (int i = 0; i < BITS_IN_INT; i++) {
        if ((i >= START_EXP_BIT && i <= END_EXP_BIT) || i == SIGN_BIT) {
            putchar('0' + get_bit(a.bits[DECIMAL_INFO], i));
        } else {
            putchar('X');
        }
    }

    putchar(':');

    putchar('\n');
}

char* decimal2str(s21_decimal a) {
    /// Convert decimal to string for debug
    char *str = calloc(256, sizeof (char));

    str[0] = ':';
    for (int i = 0; i < ALL_BIT; i++) {
        str[i + 1] = (char)('0' + get_bit(get_bits(a, i), i));
    }

    str[ALL_BIT + 1] = ':';
    for (int i = 0; i < BITS_IN_INT; i++) {
        if ((i >= START_EXP_BIT && i <= END_EXP_BIT) || i == SIGN_BIT) {
            str[ALL_BIT + i + 1] = (char)('0' + get_bit(a.bits[DECIMAL_INFO], i));
        } else {
            str[ALL_BIT + i + 1] = 'X';
        }
    }

    str[ALL_BIT + BITS_IN_INT + 1] = ':';

    return str;
}

