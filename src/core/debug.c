//
// Created by Nana Daughterless on 6/4/22.
//

#include "decimal_core.h"

void print_decimal(s21_decimal a) {
  /// Print Decimal

  putchar(':');
  for (int i = 0; i < ALL_BIT; i++) {
    if (!(i % 32)) putchar('-');
    putchar('0' + get_bit(get_bits(a, i), i));
  }

  putchar(':');
  for (int i = 0; i < BITS_IN_INT; i++) {
    if ((i >= START_EXP_BIT && i <= END_EXP_BIT) || i == SIGN_BIT) {
      putchar('0' + get_bit(a.bits[DECIMAL_INFO], i));
    } else {
      putchar('X');
    }
  }

  putchar(':');

  putchar('\n');
}

void d_print_decimal(s21_decimal a) {
  char string[512] = "echo \"";
  strcat(string, decimal2str(a));
  strcat(string, "\" | python3 conv.py | grep -e FINALY");
  printf("%s\n", string);
  system(string);
}

char* decimal2str(s21_decimal a) {
  /// Convert decimal to string for debug
  char* str = calloc(256, sizeof(char));
  int shift = 0;
  str[shift++] = ':';
  for (int i = 0; i < ALL_BIT; i++) {
    if (!(i % 32)) str[i + shift++] = '-';
    str[i + shift] = (char)('0' + get_bit(get_bits(a, i), i));
  }

  str[ALL_BIT + shift++] = ':';
  for (int i = 0; i < BITS_IN_INT; i++) {
    if ((i >= START_EXP_BIT && i <= END_EXP_BIT) || i == SIGN_BIT) {
      str[ALL_BIT + i + shift] = (char)('0' + get_bit(a.bits[DECIMAL_INFO], i));
    } else {
      str[ALL_BIT + i + shift] = 'X';
    }
  }

  str[ALL_BIT + BITS_IN_INT + shift] = ':';

  return str;
}
