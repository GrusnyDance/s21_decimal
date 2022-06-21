#include "decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_code = OK;
  int sign = (src < 0) ? 1 : 0;

  if (!dst) return CONVERTION_ERROR;
  if (isinf(src) || isnan(src)) {
    set_null(dst);
    return CONVERTION_ERROR;
  }

  union convert {
    float src;
    int res;
  } conv = {src};

  set_null(dst);
  conv.src = fabs(src);
  int exp = (conv.res >> 23) - 127;

  if (exp > -95 && exp <= 95) {
    double reserve = fabs(src);
    int ten_pow = 0;
    for (int i = 0; ten_pow < 28 && reserve < (int)pow(2, 21); i++, ten_pow++) {
      reserve *= 10;
    }
    reserve = (float)reserve;
    while (fmod(reserve, 10.0) == 0 && ten_pow > 0) {
      reserve /= 10;
      ten_pow -= 1;
    }
    float final_float = reserve;
    union convert finconv = {final_float};
    int final_num = finconv.res;
    int new_exp = (final_num >> 23) - 127;
    dst->bits[new_exp / 32] = 1 << (new_exp % 32);
    for (int j = new_exp - 1, k = 22; k >= 0; j--, k--) {
      if (final_num & (1 << k)) dst->bits[j / 32] |= (1 << (j % 32));
    }
    if (sign) dst->bits[3] |= 1 << 31;
    dst->bits[3] |= ten_pow << 16;
  } else {
    return_code = CONVERTION_ERROR;
  }
  return return_code;
}
