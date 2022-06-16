// gcc -o test test.c $(pkg-config --libs --cflags gmp)
// -I/usr/local/Cellar/gmp/6.2.1_1/include -L/usr/local/Cellar/gmp/6.2.1_1/lib
// -lgmp
#if defined(__linux__)
#include "./gmp-6.2.1/gmp.h"
#else
#include <gmp.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../arithmetic/decimal_arithmetic.h"

double call_s21_func(int a, int sign1, int pow1, int b, int sign2, int pow2);

int main () {
  int a, b;
  double a_float, b_float;
  double res_21, res;
  srand(time(NULL));
  int sign1, sign2;
  int pow1, pow2;

  a = rand() % 2147483647;
  b = rand() % 2147483647;
  pow1 = rand() % 10;
  pow2 = rand() % 10;
  sign1 = rand() % 2;
  sign2 = rand() % 2;

  res_21 = call_s21_func(a, sign1, pow1, b, sign2, pow2);

  if (sign1) a *= -1;
  if (sign2) b *= -1;

  a_float = (double)a / (pow(10, pow1));
  b_float = (double)b / (pow(10, pow2));

  printf("num1 is %lf\n", a_float);
  printf("num2 is %lf\n\n", b_float);

  res = fmodl(a_float, b_float);

  printf("original res is %lf\n", res);
  printf("s21 res is %lf\n", res_21);

  double diff = res - res_21;

  if (diff < 0.0000001 && diff > -0.0000001) {
    printf("\033[32mSUCCESS\033[0m\n");
  } else {
    printf("\033[31mFAIL\033[0m\n");
  }
  return 0;
}

double call_s21_func(int a, int sign1, int pow1, int b, int sign2, int pow2) {
  s21_decimal num1, num2, result;
  int ret_val;
  double ret_double;
  int ret_int;

  for (int i = 0; i < 4; i++) {
    num1.bits[i] = 0;
    num2.bits[i] = 0;
  }

  num1.bits[0] = a;
  num2.bits[0] = b;

  if (sign1) num1.bits[3] |= 1 << 31;
  if (sign2) num2.bits[3] |= 1 << 31;

  if (pow1) num1.bits[3] |= pow1 << 16;
  if (pow2) num2.bits[3] |= pow2 << 16;

  ret_val = s21_mod(num1, num2, &result);
  if (ret_val == 1) {
    printf("division by zero\n");
    return 0.0;
  }

  ret_int = result.bits[0];
  if (result.bits[3] < 0) ret_int *= -1;

  int pow_helper = (result.bits[3] << 1) >> 17;
  ret_double = (double)ret_int / (pow(10, pow_helper));

  return ret_double;

}