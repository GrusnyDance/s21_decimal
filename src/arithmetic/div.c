#include "decimal_arithmetic.h"

s21_decimal div_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int *status) {
  s21_decimal one; s21_from_int_to_decimal(1, &one);
  s21_decimal temp = init_zero_decimal();

  if (stupid_equal(value_1, value_2)) {
    *result = one;
  } else if (stupid_less(value_1, value_2)) {
    *result = temp;
  } else {
      s21_decimal divcopy = value_2;

      // TODO replace less(a, b) || eq(a, b) -> less_or_eq(a, b)
      while ((stupid_less(value_2, value_1) || stupid_equal(value_2, value_1)) &&
             !get_gbit(value_2, ALL_BIT - 1)) {
          left_shift(&value_2);
          left_shift(result);
      }

      if (stupid_less(value_1, value_2)) {
          right_shift(&value_2);
          right_shift(result);
      }

      very_stupid_sub(value_1, value_2, &temp);
      one = div_core(temp, divcopy, &one, status);
      *status = very_stupid_add(*result, one, result, 0, 0);
  }

  return *result;
}

int int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;

  if (is_zero(value_2)) {
      status = DIV_ZERO;
  } else {
      s21_from_int_to_decimal(1, result);

      set_sign(result, get_sign(value_1) ^ get_sign(value_2));
      set_sign(&value_1, 0);
      set_sign(&value_2, 0);

      int res_exp = get_exponent(value_1) - get_exponent(value_2);
      set_exponent(&value_1, 0);
      set_exponent(&value_2, 0);

      *result = div_core(value_1, value_2, result, &status);
      if (res_exp < 0) {
          status = shifting(result, -res_exp);
          status += -res_exp << 2;

          res_exp = 0;
      }
      set_exponent(result, res_exp);
  }

  return status;
}

int additional_int_prec(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result, int status) {
  set_exponent(&value_2, get_exponent(value_2) - status);

  s21_decimal mod_res = init_zero_decimal(), div_res = init_zero_decimal();

  s21_mod(value_1, value_2, &mod_res);
  shifting(&mod_res, -1);

  set_exponent(&value_2, get_exponent(value_2) + status);

  while (stupid_less(mod_res, value_2)) bank_round(&value_2, 1);
  int_div(mod_res, value_2, &div_res);
  // d_print_decimal(*result);
  // d_print_decimal(div_res);
  status = s21_add(div_res, *result, result);
  // s21_truncate(*result, result);
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = int_div(value_1, value_2, result);
  if (!(status & 3)) {
    status >>= 2;
    s21_decimal mod_res = init_zero_decimal();
    // int value_exp = get_exponent(value_2);
    if (status) status = additional_int_prec(value_1, value_2, result, status);
    s21_truncate(*result, result);
    s21_mod(value_1, value_2, &mod_res);
    // d_print_decimal(mod_res);
    if (!is_zero(mod_res)) {
      // set_exponent(&value_2, value_exp);
      s21_decimal div_res = init_zero_decimal(), ten = {{10, 0, 0, 0}},
                  tmp = init_zero_decimal();
      int exp = get_exponent(mod_res);
      for (int sub_stat = 0; !sub_stat; tmp = init_zero_decimal()) {
        sub_stat = stupid_mul(mod_res, ten, &tmp);
        if (!sub_stat) {
          mod_res = tmp;
          if (++exp < 29) set_exponent(&mod_res, exp);
        }
      }
      if (!get_exponent(mod_res)) set_exponent(&mod_res, 28);
      // d_print_decimal(mod_res);
      // d_print_decimal(value_2);
      while (stupid_less(mod_res, value_2)) bank_round(&value_2, 1);
      int_div(mod_res, value_2, &div_res);
      if (exp > 28) set_exponent(&div_res, exp - get_exponent(value_2));
      // d_print_decimal(*result);
      // d_print_decimal(div_res);
      // set_exponent(&div_res, get_exponent(div_res) - status);
      // status = 0;

      status = s21_add(div_res, *result, result);
    }
  } else
    status &= 3;
  if (status == 1 && get_sign(value_1) ^ get_sign(value_2)) ++status;
  return status;
}