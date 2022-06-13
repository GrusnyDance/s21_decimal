//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_core.h"

int left_shift(s21_decimal *a) {
    int n = 0;
    int old;
    for (int i = 0; i < BITS_COUNT; i++) {
        int tmp = BITS_IN_INT * i;
        old = get_gbit(*a, tmp + BITS_IN_INT - 1);
        *p_get_bits(a, tmp) = set_bit(get_bits(*a, tmp) << 1, 0, n);
        n = old;
    }
    return 0;
}

int right_shift(s21_decimal *a) {
    int n = 0;
    int old;
    for (int i = BITS_COUNT - 1; i >= 0; i--) {
        int tmp = BITS_IN_INT * i;
        old = get_gbit(*a, tmp);
        *p_get_bits(a, tmp) = set_bit( get_bits(*a, tmp) >> 1, tmp - 1, n);
        n = old;
    }
    return 0;
}
//222222 - 1111111 - 000000
//022222 - 2111111 - 100000
//100000 - 2111111 - 022222
//0000000 - 111111111 - 22222222