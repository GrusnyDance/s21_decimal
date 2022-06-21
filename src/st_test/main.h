//
// Created by Nana Daughterless on 6/18/22.
//

#ifndef SRC_ST_TEST_MAIN_H_
#define SRC_ST_TEST_MAIN_H_

#define PYTHON "python3"
#define TRUNCATE_PATH " py_test/print_truncate_testcase.py"
#define ROUND_PATH " py_test/print_round_testcase.py"
#define FLOOR_PATH " py_test/print_floor_testcase.py"
#define NEGATE_PATH " py_test/print_negate_testcase.py"

#define DEC_TO_FLOAT_PATH " py_test/print_dec_to_float_testcase.py"
#define DEC_TO_INT_PATH " py_test/print_dec_to_int_testcase.py"
#define FLOAT_TO_DEC_PATH " py_test/print_float_to_dec_testcase.py"

#define REDIRECT " >> "
#define REDIRECT_FILE "input"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"

#define EPS 1e-7

static long long cur_testcase = 0;
static char **numbers;
static char **results;

#define BUFFER_SIZE 1024

s21_decimal str2decimal(const char *number);

void generate_testcase(int count, char *command_path);
void free_testcase(int count);
void get_testcase(char **number, char **result);

// another
void run_truncate_test(int count);
void run_round_test(int count);
void run_floor_test(int count);
void run_negate_test(int count);

// conversion
void run_dec_to_float_test(int count);
void run_dec_to_int_test(int count);
void run_float_to_dec_test(int count);

#endif  // SRC_ST_TEST_MAIN_H_
