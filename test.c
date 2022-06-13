//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
    s21_decimal a = {1, 0, 0, 0};
    print_decimal(a);
    for (int i = 0 ; i < 100; i++) {
        left_shift(&a);
        print_decimal(a);
    }
}