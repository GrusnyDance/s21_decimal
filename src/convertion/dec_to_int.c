#include "decimal.h"

// ВСТАВИТЬ ПРОВЕРКУ НА INF И NAN

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_code = OK;
  int ten_pow;
  //   change_endian(&src);

  *dst = src.bits[0];
  if (src.bits[3] < 0) *dst *= -1;
  ten_pow = (src.bits[3] << 1) >> 17;
  *dst /= (int)pow(10, ten_pow);
  return return_code;
}
