cmake_minimum_required(VERSION 3.22)
project(s21_decimal C)
project(st_test C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(s21_decimal
        src/s21_decimal.c
        src/s21_decimal.h
        src/core/bit.c
        src/core/sign.c
        src/core/shift.c
        src/core/exponent.c
        src/core/debug.c
        src/core/decimal.c
        src/core/decimal_core.h
        src/core/decimal.c
        src/another/s21_floor.c
        src/another/s21_truncate.c
        src/another/decimal_another.h
        src/another/balancing.c
        src/another/bank_round.c
        src/another/s21_neg.c
        src/another/s21_round.c
        src/comparison/decimal_comparison.h
        src/comparison/s21_eq.c
        src/comparison/s21_less.c
        src/comparison/s21_gr.c
        src/comparison/s21_gr_or_eq.c
        src/comparison/s21_not_eq.c
        src/comparison/s21_less_or_eq.c
        src/convertion/dec_to_float.c
        src/convertion/dec_to_int.c
        src/convertion/int_to_dec.c
        src/convertion/float_to_dec.c
        src/convertion/shared.c
        src/arithmetic/add.c
        src/arithmetic/sub.c
        src/arithmetic/mul.c
        src/arithmetic/div.c
        src/arithmetic/fmod.c
        src/MyLib/style.h
        test.c
        )

add_executable(st_test
        src/s21_decimal.c
        src/s21_decimal.h
        src/core/bit.c
        src/core/sign.c
        src/core/shift.c
        src/core/exponent.c
        src/core/debug.c
        src/core/decimal.c
        src/core/decimal_core.h
        src/core/decimal.c
        src/another/s21_floor.c
        src/another/s21_truncate.c
        src/another/decimal_another.h
        src/another/balancing.c
        src/another/bank_round.c
        src/another/s21_neg.c
        src/another/s21_round.c
        src/comparison/decimal_comparison.h
        src/comparison/s21_eq.c
        src/comparison/s21_less.c
        src/comparison/s21_gr.c
        src/comparison/s21_gr_or_eq.c
        src/comparison/s21_not_eq.c
        src/comparison/s21_less_or_eq.c
        src/convertion/dec_to_float.c
        src/convertion/dec_to_int.c
        src/convertion/int_to_dec.c
        src/convertion/float_to_dec.c
        src/convertion/shared.c
        src/arithmetic/add.c
        src/arithmetic/sub.c
        src/arithmetic/mul.c
        src/arithmetic/div.c
        src/arithmetic/fmod.c
        src/MyLib/style.h

        src/st_test/main.c
        src/st_test/truncate_test.c
        src/st_test/floor_test.c
        src/st_test/round_test.c
        src/st_test/negate_test.c
        src/st_test/dec_to_float_test.c
        )

target_link_libraries(s21_decimal m)
target_link_libraries(st_test m)
