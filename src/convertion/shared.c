#include "decimal.h"

void change_endian(s21_decimal *my_struct) {
  for (int i = 0; i < 4; i++) {
    int temp = 0;
    for (int j = 0, k = 31; j <= 31; j++, k--) {
      if (my_struct->bits[i] & (1u << j)) {
        temp |= 1u << k;
      }
    }
    my_struct->bits[i] = temp;
  }
}

void set_sign2(s21_decimal *my_struct) { my_struct->bits[3] |= 1u << 31; }

void set_null(s21_decimal *my_struct) {
  for (int i = 0; i < 4; i++) {
    my_struct->bits[i] = 0;
  }
}
