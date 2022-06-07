//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_comparison.h"

int stupid_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = ALL_BIT - 1; i >= 0; i--) {
    if (get_gbit(value_1, i) == get_gbit(value_2, i))
      continue;
    else if (get_gbit(value_1, i) < get_gbit(value_2, i)) {
      res = 1;
      break;
    } else
      break;
  }
  return res;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  balancing(&a, &b);
  int res = false;

  if (get_sign(a) > get_sign(b)) {
    res = true;
  } else {
    res = stupid_less(a, b);
  }

  return res;
}
