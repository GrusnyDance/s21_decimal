//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    for (int i = 0 ; i < 100000; i++) {
        int inp1 = (rand() % 128) * ((rand() % 2)? -1 : 1);
        int inp2 = (rand() % 128) * ((rand() % 2)? -1 : 1);

        int res = inp1 * inp2;
        s21_decimal a = {abs(inp1), 0, 0, 0};
        set_sign(&a, inp1 < 0);
        set_exponent(&a, 0);
        s21_decimal b = {abs(inp2), 0, 0, 0};
        set_sign(&b, inp2 < 0);
        set_exponent(&b, 0);

        s21_decimal c = {0, 0, 0, 0};
        s21_decimal res_d= {abs(res), 0, 0, 0};
        set_sign(&res_d, res < 0);

        printf("%d\n", s21_mul(a, b, &c));
        if (!s21_is_equal(res_d, c)) {
            print_decimal(a);
            print_decimal(b);
            print_decimal(c);
            print_decimal(res_d);
            putchar('\n');
        }
    }
}