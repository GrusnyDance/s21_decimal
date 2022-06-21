#include "../s21_decimal.h"
#include "decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_code = OK;
  int ten_pow = (src.bits[3] << 1) >> 17;

  if (!dst) {
    return_code = CONVERTION_ERROR;
  } else if (ten_pow > 28) {
    *dst = 0;
    return_code = CONVERTION_ERROR;
  } else {
    s21_truncate(src, &src);
    if (get_sign(src) == NEGATIVE)
      *dst = 0 - src.bits[0];
    else
      *dst = src.bits[0];
    if (*dst) *dst = set_bit(*dst, 31, get_sign(src));
  }
  return return_code;
}
