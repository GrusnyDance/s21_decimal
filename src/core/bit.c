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
        bits = on_bit(bits, bit);
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

int is_zero(s21_decimal a) {
    return !a.bits[0] && !a.bits[1] && !a.bits[2];
}