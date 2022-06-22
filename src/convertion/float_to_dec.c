#include "decimal.h"

typedef union {
  float float_num;
  int int_num;
} conv;

int get_ten_pow(double num) {
  double frac;
  double integer;
  int null_counter = 0;
  frac = modf(num, &integer);
  frac *= 10;
  int ten_pow = 0;
  for (int i = 0; i < 29; i++, ten_pow++) {
    frac = modf(frac, &integer);
    if (i < 28) {
      if (integer == 0)
        null_counter++;
      else
        null_counter = 0;
    }
    frac *= 10;
  }
  return (ten_pow - 1 - null_counter);
}

int add_int_part(s21_decimal *temp, int *ten_pow, double num) {
  s21_decimal first_num, second_num, res, ten_dec, mul_helper;
  set_null(&res);
  int pow_helper = 0;
  int stop_flag = 0;
  int ret_val = 1;
  double frac;
  double int_num;
  frac = modf(num, &int_num);
  frac = fmod(int_num, 10.0);
  s21_from_int_to_decimal(10, &ten_dec);
  s21_from_int_to_decimal(1, &second_num);

  while ((int)int_num != 0) {
    s21_from_int_to_decimal((int)frac, &first_num);
    if (pow_helper > 0) {
      if (!stop_flag) stop_flag = s21_mul(second_num, ten_dec, &second_num);
    }
    if (!stop_flag) stop_flag = s21_mul(first_num, second_num, &mul_helper);
    if (!stop_flag) stop_flag = s21_add(mul_helper, res, &res);
    pow_helper++;
    int_num /= 10;
    frac = fmod(int_num, 10.0);
  }
  // for (int i = 0; i < 4; i++) {
  //   for (int j = 31; j >= 0; j--) {
  //     if (res.bits[i] & (1 << j))
  //       printf("1");
  //     else
  //       printf("0");
  //   }
  //   printf(" ");
  // }
  // printf("\n");
  while (ret_val != 0) {
    if ((*ten_pow) != 0) {
      s21_from_int_to_decimal(10, &first_num);
      for (int j = 0; j < ((*ten_pow) - 1); j++) {
        s21_mul(first_num, ten_dec, &first_num);
      }
      ret_val = s21_mul(res, first_num, &second_num);
      for (int i = 0; i < 4; i++) {
        temp->bits[i] = second_num.bits[i];
      }
      if (ret_val != 0) (*ten_pow)--;
    } else {
      for (int i = 0; i < 4; i++) {
        temp->bits[i] = res.bits[i];
      }
      break;
    }
  }
  return stop_flag;
}

void add_frac_part(s21_decimal *temp, int ten_pow, double num) {
  s21_decimal first_num, second_num, res, ten_dec, mul_helper;
  set_null(&res);
  for (int k = 0; k < 4; k++) {
    res.bits[k] = temp->bits[k];
  }
  int stop_flag = 0;
  double frac;
  double int_num;
  frac = modf(num, &int_num);
  frac *= 10;
  frac = modf(frac, &int_num);
  s21_from_int_to_decimal(10, &ten_dec);
  s21_from_int_to_decimal(1, &second_num);

  for (int i = 0; i < ten_pow; i++) {
    if ((int)int_num == 0) {
      frac *= 10;
      frac = modf(frac, &int_num);
      continue;
    }
    s21_from_int_to_decimal((int)int_num, &first_num);
    for (int j = 0; j < (ten_pow - (i + 1)); j++) {
      if (!stop_flag) stop_flag = s21_mul(second_num, ten_dec, &second_num);
    }
    if (!stop_flag) stop_flag = s21_mul(first_num, second_num, &mul_helper);
    if (!stop_flag) stop_flag = s21_add(mul_helper, res, &res);
    s21_from_int_to_decimal(1, &second_num);
    frac *= 10;
    frac = modf(frac, &int_num);
  }
  for (int i = 0; i < 4; i++) {
    temp->bits[i] = res.bits[i];
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_code = OK;
  int sign = (src < 0) ? 1 : 0;

  if (!dst || isinf(src) || isnan(src)) {
      set_null(dst);
      return_code = CONVERTION_ERROR;
  } else {
      set_null(dst);
      conv union_first;
      union_first.float_num = fabsf(src);
      int exp = (union_first.int_num >> 23) - 127;
      s21_decimal temp;
      set_null(&temp);

      if (exp > -95 && exp <= 95) {
          double reserve = fabsf(src);
          int ten_pow = get_ten_pow(reserve);

          return_code = add_int_part(&temp, &ten_pow, reserve);
          // for (int i = 0; i < 4; i++) {
          //   for (int j = 31; j >= 0; j--) {
          //     if (temp.bits[i] & (1 << j))
          //       printf("1");
          //     else
          //       printf("0");
          //   }
          //   printf(" ");
          // }
          // printf("\n");
          // }
          if (!return_code) {
              if (ten_pow != 0) add_frac_part(&temp, ten_pow, reserve);
              for (int i = 0; i < 4; i++) dst->bits[i] = temp.bits[i];
              if (sign) dst->bits[3] |= 1 << 31;
              dst->bits[3] |= ten_pow << 16;
          }
      }
  }

  return return_code;
}
