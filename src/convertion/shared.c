#include "decimal.h"

void set_null(s21_decimal *my_struct) {
  for (int i = 0; i < 4; i++) {
    my_struct->bits[i] = 0;
  }
}
