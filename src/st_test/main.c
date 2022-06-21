//
// Created by Nana Daughterless on 6/18/22.
//

#include "main.h"

void generate_testcase(int count, char *command_path) {
  char command[BUFFER_SIZE] = "";

  sprintf(command, "%s%s %d %s%s", PYTHON, command_path, count, REDIRECT,
          REDIRECT_FILE);

  system(command);

  numbers = calloc(count + 1, sizeof(char *));
  results = calloc(count + 1, sizeof(char *));

  if (!strcmp(command_path, EQ_PATH) || !strcmp(command_path, LESS_PATH)) {
    results2 = calloc(count + 1, sizeof (char *));
  }

  FILE *file = fopen(REDIRECT_FILE, "r");
  for (int i = 0; i < count; i++) {
    numbers[i] = calloc(BUFFER_SIZE, sizeof(char));
    results[i] = calloc(BUFFER_SIZE, sizeof(char));

    fscanf(file, "%s\n", numbers[i]);
    fscanf(file, "%s\n", results[i]);

    if (results2) {
      results2[i] = calloc(BUFFER_SIZE, sizeof(char));
      fscanf(file, "%s\n", results2[i]);
    }
  }
  fclose(file);
}

void free_testcase(int count) {
  for (int i = 0; i < count; i++) {
    free(numbers[i]);
    free(results[i]);
    if (results2 && results2[i]) {
      free(results2[i]);
    }
  }
  free(numbers);
  free(results);

  if (results2)
    free(results2);

  numbers = NULL;
  results = NULL;
  results2 = NULL;

  cur_testcase = 0;
}

void get_testcase(char **number, char **result) {
  *number = numbers[cur_testcase];
  *result = results[cur_testcase];

  cur_testcase++;
}

void get_testcase2(char **result2) {
  *result2 = results2[cur_testcase - 1];
}

s21_decimal str2decimal(const char *number) {
  s21_decimal res = {0, 0, 0, 0};

  int cur_sim_in_num = 0;
  for (int i = BITS_IN_INT - 1; i >= 0; i--) {
    if (number[cur_sim_in_num++] - '0')
      res.bits[DECIMAL_INFO] = set_bit(res.bits[DECIMAL_INFO], i, 1);
  }

  for (int i = ALL_BIT - 1; i >= 0; i--) {
    if (number[cur_sim_in_num++] - '0')
      *p_get_bits(&res, i) = set_bit(get_bits(res, i), i, 1);
  }

  return res;
}

void clear_input() {
  char command[BUFFER_SIZE] = "";
  sprintf(command, "rm -f %s", REDIRECT_FILE);
  system(command);
}

int main() {
  clear_input();

  for (int i = 0; i < 1000; i++) {
//    printf(COLOR_GREEN "TRUNCATE:\n" COLOR_END);
//    run_truncate_test(10);
//
//    clear_input();
//    printf(COLOR_GREEN "ROUND:\n" COLOR_END);
//    run_round_test(10);
//
//    clear_input();
//    printf(COLOR_GREEN "FLOOR:\n" COLOR_END);
//    run_floor_test(10);
//
//    clear_input();
//    printf(COLOR_GREEN "NEGATE:\n" COLOR_END);
//    run_negate_test(10);
//
//    clear_input();
//    printf(COLOR_GREEN "DEC_TO_FLOAT:\n" COLOR_END);
//    run_dec_to_float_test(10);
//    clear_input();
//
//      clear_input();
//      printf(COLOR_GREEN "DEC_TO_INT:\n" COLOR_END);
//      run_dec_to_int_test(10);
//      clear_input();

//      clear_input();
//      printf(COLOR_GREEN "FLOAT_TO_DEC:\n" COLOR_END);
//      run_float_to_dec_test(10);
//      clear_input();

//      clear_input();
//      printf(COLOR_GREEN "INT_TO_DEC:\n" COLOR_END);
//      run_int_to_dec_test(10);
//      clear_input();

//      clear_input();
//      printf(COLOR_GREEN "EQ TEST:\n" COLOR_END);
//      run_eq_test(10);
//      clear_input();

      clear_input();
      printf(COLOR_GREEN "LESS TEST:\n" COLOR_END);
      run_less_test(10);
      clear_input();

      printf("\n");
  }

  return 0;
}