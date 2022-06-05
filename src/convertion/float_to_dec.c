#include "decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_code = OK;
  int sign = (src < 0) ? 1 : 0;
  src = fabs(src);
  set_null(dst);
  int exp = ((*(int *)&src) >> 23) - 127;
  int new_exp;
  float final_float;
  int final_num;

  if (isinf(src) || isnan(src)) return_code = CONVERTION_ERROR;
  if (!dst) {
    return_code = CONVERTION_ERROR;
  } else if (exp > -95 && exp <= 95) {
    double reserve = (double)src;
    int ten_pow = 0;
    for (int i = 0; ten_pow < 28 && reserve < (int)pow(2, 21); i++, ten_pow++) {
      reserve *= 10;
    }
    reserve = (float)reserve;
    while (fmod(reserve, 10.0) == 0 && ten_pow > 0) {
      reserve /= 10;
      ten_pow -= 1;
    }
    final_float = reserve;
    final_num = (*(int *)&final_float);
    new_exp = (final_num >> 23) - 127;
    dst->bits[new_exp / 32] = 1 << (new_exp % 32);
    for (int j = new_exp - 1, k = 22; k >= 0; j--, k--) {
      if (final_num & (1 << k)) dst->bits[j / 32] |= (1 << (j % 32));
    }
    if (sign) set_sign(dst);
    dst->bits[3] |= ten_pow << 16;
    // change_endian(dst);
  }
  return return_code;
}