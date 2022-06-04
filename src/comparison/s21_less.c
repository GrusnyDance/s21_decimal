//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_comparison.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
    balancing(&a, &b);
    int res = false;

    if (get_sign(a) > get_sign(b)) {
        res = true;
    } else {
        s21_decimal int_d_a, int_d_b;
        s21_truncate(a, &int_d_a);
        s21_truncate(b, &int_d_b);

        for (int i = ALL_BIT - 1; !res && i >= 0; i--) {
            if (get_gbit(int_d_b, i) - get_gbit(int_d_a, i) > 0) {
                res = true;
            } elif (get_gbit(int_d_b, i) - get_gbit(int_d_a, i) < 0) {
                break;

            }
        }

        if (!res) {
            s21_decimal mod_d_a, mod_d_b;
            s21_sub(a, int_d_a, &mod_d_a);
            s21_sub(b, int_d_b, &mod_d_b);

            for (int i = ALL_BIT - 1; !res && i >= 0; i--) {
                if (get_gbit(mod_d_b, i) - get_gbit(mod_d_a, i) > 0) {
                    res = true;
                } elif (get_gbit(mod_d_b, i) - get_gbit(mod_d_a, i) < 0) {
                    break;
                }
            }
        }
    }

    return res;
}
