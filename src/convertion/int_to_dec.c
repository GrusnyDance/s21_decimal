#include "decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_code = OK;
  set_null(dst);

  if (dst) {
    if (src < 0) {
      set_sign2(dst);
      dst->bits[0] = 0 - src;
    } else
      dst->bits[0] = src;
    // change_endian(dst);  // TBC
  } else {
    return_code = CONVERTION_ERROR;
  }
  return return_code;
}