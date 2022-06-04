//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_another.h"

int balancing(s21_decimal *a, s21_decimal *b) {
    int status = 0;

    if (get_exponent(*a) > get_exponent(*b)) {
        return balancing(b, a);
    } elif (get_exponent(*a) < get_exponent(*b)) {
        
    }

    return status;
}
