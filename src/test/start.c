// gcc -o test test.c $(pkg-config --libs --cflags gmp)
// -I/usr/local/Cellar/gmp/6.2.1_1/include -L/usr/local/Cellar/gmp/6.2.1_1/lib
// -lgmp
#if defined(__linux__)
#include "./gmp-6.2.1/gmp.h"
#else
#include <gmp.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_bits(mpz_t var);

int main() {
  gmp_randstate_t rstate;
  gmp_randinit_default(rstate);
  gmp_randseed_ui(rstate, time(NULL));
  srand(time(NULL));
  mpz_t n, m;
  int two_pow;
  mpz_init2(m, 128);
  mpz_init2(n, 128);  // очищается только то что инициализировано
  for (int i = 0; i < 10; i++) {
    two_pow = rand() % 96;
    mpz_ui_pow_ui(n, 2, two_pow);
    mpz_urandomm(m, rstate, n);  // range 2n-1 to 2n-1, inclusive
    print_bits(m);
  }
  gmp_randclear(rstate);
  mpz_clear(n);
  return 0;
}

void print_bits(mpz_t var) {
  mpz_t tmp, res;
  mpz_init2(res, 128);
  mpz_init2(tmp, 128);
  mpz_ui_pow_ui(tmp, 2, 127);
  gmp_printf("\n%Zd\n", tmp);
  for (int i = 127; i >= 0; i--) {
    mpz_ui_pow_ui(tmp, 2, i);
    mpz_and(res, tmp, var);
    if (mpz_cmp_ui(res, 0)) {
      printf("\033[33m1\033[0m");
    } else {
      printf("0");
    }
  }
  mpz_clear(tmp);
  mpz_clear(res);
}
