// gcc -o test test.c $(pkg-config --libs --cflags gmp)
// -I/usr/local/Cellar/gmp/6.2.1_1/include -L/usr/local/Cellar/gmp/6.2.1_1/lib
// -lgmp
#if defined(__linux__)
#include "./gmp-6.2.1/gmp.h"
#else
#include <gmp.h>
#endif
#include <stdio.h>

int main() {
  mpz_t r, n, m;
  mpz_inits(r, n, m);   // очищается только то что инициализировано
  mpz_set_ui(n, 0b0000000000001);
  mpz_set_ui(m, 3);
  mpz_add(r, n, m);
  gmp_printf("%Zd\n", r);
  mpz_clears(r);
  return 0;
}

// https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html
// https://gmplib.org/manual/Integer-Arithmetic#Integer-Arithmetic
// https://gmplib.org/gmp-man-6.2.1.pdf
// https://www.mitchr.me/SS/exampleCode/GMP.html
// http://cuiaoxiang.github.io/2013/10/02/gmp-introduction/