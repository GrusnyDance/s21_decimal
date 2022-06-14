//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
  s21_decimal a = {100, 0, 0, 0}, b = {3, 0, 0, 0}, c;
  s21_from_int_to_decimal(2, &a);
  s21_from_int_to_decimal(3, &b);
  set_exponent(&a, 0);
  set_exponent(&b, 0);
  d_print_decimal(a);
  d_print_decimal(b);
  s21_div(a, b, &c);
  d_print_decimal(c);
}