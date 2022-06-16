//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_core.h"

void print_decimal(s21_decimal a) {
  /// Print Decimal

  putchar(':');
  for (int i = BITS_IN_INT - 1; i >= 0; i--) {
      int tmp = get_bit(a.bits[DECIMAL_INFO], i);
    if ((i >= START_EXP_BIT && i <= END_EXP_BIT) || i == SIGN_BIT) {
      if (tmp) {
        printf("%s%c%s", COLOR_RED, '1', COLOR_END);
      } else {
        putchar('0');
      }
    } else {
      printf("%s%c%s", COLOR_ORANGE, 'O' + tmp, COLOR_END);
    }
  }

  putchar(':');
  for (int i = ALL_BIT - 1; i >= 0; i--) {
    if (!((i + 1) % 32)) putchar('-');
    int tmp = get_gbit(a, i);
    if (tmp)
      printf("%s%c%s", COLOR_RED, '1', COLOR_END);
    else
      putchar('0');
  }

  putchar(':');

  putchar('\n');
}

void d_print_decimal(s21_decimal a) {
  char string[512] = "echo \"";
  char *new_str = decimal2str(a);

  strcat(string, new_str);
  free(new_str);

  strcat(string, "\" | python3 conv.py | grep FINALY");
  printf("%s\n", string);
  system(string);
}

char* decimal2str(s21_decimal a) {
  /// Convert decimal to string for debug
    char* str = calloc(512, sizeof(char));
    int shift = 0;

    str[shift++] = ':';

    for (int i = BITS_IN_INT - 1; i >= 0; i--, shift++) {
        if ((i >= START_EXP_BIT && i <= END_EXP_BIT) || i == SIGN_BIT) {
            str[shift] = (char)('0' + get_bit(a.bits[DECIMAL_INFO], i));
        } else {
            str[shift] = (char)('O' + get_bit(a.bits[DECIMAL_INFO], i));
        }
    }

    str[shift++] = ':';
    for (int i = ALL_BIT - 1; i >= 0; i--, shift++) {
        if (!((i + 1) % 32))
            str[shift++] = '-';
        str[shift] = (char)('0' + get_bit(get_bits(a, i), i));
    }


  str[shift] = ':';

  return str;
}
