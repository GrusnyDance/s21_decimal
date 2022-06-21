//
// Created by Nana Daughterless on 6/5/22.
//

#include "decimal_core.h"

s21_decimal init_zero_decimal() {
  s21_decimal new_decimal = {{0, 0, 0, 0}};
  return new_decimal;
}

s21_decimal init_random_decimal() {
  s21_decimal new_decimal = {
      {rand() * ((rand() % 2) ? -1 : 1), rand() * ((rand() % 2) ? -1 : 1),
       rand() * ((rand() % 2) ? -1 : 1), rand() * ((rand() % 2) ? -1 : 1)}};
  return new_decimal;
}
