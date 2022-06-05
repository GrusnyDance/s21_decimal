#include "decimal.h"

// ПОДУМАТЬ КАК ВОЗВРАЩАЕТСЯ КОД ОШИБКИ

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int return_code = OK;
  double reserve = 0;
  int ten_pow = 0;
  int sign;
//   change_endian(&src);

  for (int i = 0; i < 96; i++)
    if (src.bits[i / 32] & (1 << (i % 32))) reserve += pow(2, i);
  sign = (src.bits[3] < 0) ? 1 : 0;
  ten_pow = (src.bits[3] << 1) >> 17;
  if (ten_pow > 0) {
    for (int i = ten_pow; i > 0; i--) {
      reserve /= 10;
    }
  }
  *dst = (float)reserve;
  if (sign) *dst *= -1;
  return return_code;
}