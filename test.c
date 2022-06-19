//
// Created by Nana Daughterless on 6/3/22.
//

#include "src/s21_decimal.h"
#include "stdio.h"

int main() {
  s21_decimal a = {185079, -1, -1, 0}, b = {83488, -1, 324434333, 0}, c;
  // s21_from_int_to_decimal(2, &a);
  // s21_from_int_to_decimal(3, &b);
  set_sign(&a, 1);
  set_sign(&a, 1);
  set_exponent(&a, 0);
  set_exponent(&b, 2);
  d_print_decimal(a);
  d_print_decimal(b);
  s21_div(a, b, &c);
  // bank_round(&a, 1);
  // d_print_decimal(b);
  // shifting(&a, 1);
  // d_print_decimal(a);
  // printf("%d\n", s21_mul(a, b, &c));
  d_print_decimal(c);
  return 0;
}
