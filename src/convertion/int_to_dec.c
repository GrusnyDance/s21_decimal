#include "decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_code = OK;
  if (!dst) {
    return_code = CONVERTION_ERROR;
  } else {
    set_null(dst);
    if (src < 0) {
      set_sign2(dst);
      dst->bits[0] = 0 - src;
    } else {
      dst->bits[0] = src;
    }
  }
  return return_code;
}
