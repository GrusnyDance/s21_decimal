//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

int on_bit(int bits, int bit) {
    /// Return new_bits with on needed bit
    return bits | _2(bit % BITS_IN_INT);
}

int off_bit(int bits, int bit) {
    /// Return new_bits with off needed bit
    return bits & ~(_2(bit % BITS_IN_INT));
}

int is_bit(int bits, int bit) {
    /// Return 1 if was needed bit else 0
    return (bits & (_2(bit % BITS_IN_INT))) != 0;
}

int get_bit(int bits, int bit) {
    /// Full copy is_bit
    return is_bit(bits, bit % BITS_IN_INT);
}

int get_gbit(s21_decimal a, int gbit) {
    /// Full copy is_bit
    return get_bit(get_bits(a, gbit), gbit);
}

int set_bit(int bits, int bit, int new_bit) {
    /// Sets the desired bit to a certain position
    if (new_bit) {
        bits |= _2(bit % BITS_IN_INT);
    } else {
        bits = off_bit(bits, bit);
    }
    return bits;
}

int get_bits(s21_decimal a, int global_ind) {
    /// Returns the required set with bits
    return a.bits[(global_ind % ALL_BIT) / BITS_IN_INT];
}

int* p_get_bits(s21_decimal *a, int global_ind) {
    /// Returns the required pointer set with bits
    return a->bits + ((global_ind % ALL_BIT) / BITS_IN_INT);
}


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
    /// Print Decimal
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
