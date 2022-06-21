#include "decimal_comparison.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_equal(a, b) || s21_is_less(a, b);
}
