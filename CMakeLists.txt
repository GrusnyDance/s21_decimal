cmake_minimum_required(VERSION 3.22)
project(s21_decimal C)

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
        src/core/decimal_core.h
        src/another/s21_floor.c
        src/another/s21_truncate.c
        src/another/decimal_another.h
        src/another/balancing.c
        src/another/bank_round.c
        src/another/s21_neg.c
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
