CC = gcc -g #-fsanitize=address

SOURCES:= ../core/bit.c \
	../core/sign.c \
	../core/shift.c \
	../core/exponent.c \
	../core/debug.c \
	../core/decimal.c \
	../another/s21_floor.c \
	../another/s21_truncate.c \
	../another/balancing.c \
	../another/bank_round.c \
	../another/s21_neg.c \
	../another/s21_round.c \
	../comparison/s21_eq.c \
	../comparison/s21_less.c \
	../comparison/s21_gr.c \
	../comparison/s21_gr_or_eq.c \
	../comparison/s21_not_eq.c \
	../comparison/s21_less_or_eq.c \
	../convertion/int_to_dec.c \
	../convertion/float_to_dec.c \
	../convertion/dec_to_float.c \
	../convertion/dec_to_int.c \
	../convertion/shared.c \
	../arithmetic/add.c \
	../arithmetic/sub.c \
	../arithmetic/mul.c \
	../arithmetic/div.c \
	../arithmetic/fmod.c \

OBJECTS:= $(SOURCES:.c=.o)
RM:= rm -rf

# all: test_add test_sub test_mul test_add test_div
PHONY: all

main: $(SOURCES) $(OBJECTS) main_tests.c
	@$(CC) $(OBJECTS) main_tests.c -o $@ -lgmp -lcheck -lm  -lpthread -lrt -lsubunit
	./main
	@rm -rf main

test_int_add: $(SOURCES) $(OBJECTS) addition_test.c
	@$(CC) $(OBJECTS) addition_test.c -o $@ -lgmp -lm
	./test_int_add
	@rm -rf test_int_add

test_int_sub: $(SOURCES) $(OBJECTS) subtraction_test.c
	@$(CC) $(OBJECTS) subtraction_test.c -o $@ -lgmp -lm
	./test_int_sub
	@rm -rf test_int_sub

test_int_mul: $(SOURCES) $(OBJECTS) multiplication_test.c
	@$(CC) $(OBJECTS) multiplication_test.c -o $@ -lgmp -lm
	./test_int_mul
	@rm -rf test_int_mul

test_int_div: $(SOURCES) $(OBJECTS) division_test.c
	@$(CC) $(OBJECTS) division_test.c -o $@ -lgmp -lm
	./test_int_div
	@rm -rf test_int_div

test_float_add: $(SOURCES) $(OBJECTS) float_addition_test.c
	@$(CC) $(OBJECTS) float_addition_test.c -o $@ -lgmp -lm
	./test_float_add
	@rm -rf test_float_add

test_float_sub: $(SOURCES) $(OBJECTS) float_subtraction_test.c
	@$(CC) $(OBJECTS) float_subtraction_test.c -o $@ -lgmp -lm
	./test_float_sub
	@rm -rf test_float_sub

test_float_mul: $(SOURCES) $(OBJECTS) float_multiplication_test.c
	@$(CC) $(OBJECTS) float_multiplication_test.c -o $@ -lgmp -lm
	./test_float_mul
	@rm -rf test_float_mul

test_float_div: $(SOURCES) $(OBJECTS) float_division_test.c
	@$(CC) $(OBJECTS) float_division_test.c -o $@ -lgmp -lm
	./test_float_div
	@rm -rf test_float_div

test_float_fmod: $(SOURCES) $(OBJECTS) float_fmod.c
	@$(CC) $(OBJECTS) float_fmod.c -o $@ -lgmp -lm
	./test_float_fmod
	@rm -rf test_float_fmod

%.o: %.c
	@$(CC) -c $< -o $@ -lm

clean:
	@$(RM) ../another/*.o \
	../arithmetic/*.o \
	../comparison/*.o \
	../convertion/*.o \
	../core/*.o \
	*out \
	*.o test_int_add test_int_sub \
	test_int_mul test_int_div \
	test_float_add test_float_sub \
	test_float_div test_float_mul

rebuild: clean test