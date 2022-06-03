cmake_minimum_required(VERSION 3.22)
project(s21_decimal C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(s21_decimal
        src/s21_decimal.c
        src/s21_decimal.h src/core/sign.c src/core/decimal_core.h src/another/s21_floor.c src/another/decimal_another.h src/comparison/decimal_comparison.h src/comparison/s21_less.c src/MyLib/style.h test.c src/core/exponent.c src/MyLib/bit.h)
