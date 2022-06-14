CC = gcc #-g -fsanitize=address

SOURCES:= ../core/bit.c \
	../core/sign.c \
	../core/shift.c \
	../core/exponent.c \
	../core/debug.c \
	../core/decimal.c \
	../core/decimal_core.h \
	../another/s21_floor.c \
	../another/s21_truncate.c \
	../another/decimal_another.h \
	../another/balancing.c \
	../another/bank_round.c \
	../another/s21_neg.c \
	../another/s21_round.c \
	../comparison/decimal_comparison.h \
	../comparison/s21_eq.c \
	../comparison/s21_less.c \
	../comparison/s21_gr.c \
	../comparison/s21_gr_or_eq.c \
	../comparison/s21_not_eq.c \
	../comparison/s21_less_or_eq.c \
	../convertion/decimal.h \
	../convertion/int_to_dec.c \
	../convertion/float_to_dec.c \
	../convertion/dec_to_float.c \
	../convertion/dec_to_int.c \
	../convertion/shared.c \
	../arithmetic/decimal_arithmetic.h \
	../arithmetic/add.c \
	../arithmetic/sub.c \
	../arithmetic/mul.c \
	../arithmetic/div.c \
	../arithmetic/fmod.c \
	../MyLib/style.h

OBJECTS:= $(SOURCES:.c=.o)
RM:= rm -rf

# all: test_add test_sub test_mul test_add test_div
PHONY: all

test_add: $(OBJECTS) addition_test.c
	@$(CC) $(OBJECTS) addition_test.c -o $@ -lgmp -lm
	./test_add
	@rm -rf test_add

test_sub: $(OBJECTS) subtraction_test.c
	@$(CC) $(OBJECTS) subtraction_test.c -o $@ -lgmp -lm
	./test_sub
	@rm -rf test_sub

test_mul: $(OBJECTS) multiplication_test.c
	@$(CC) $(OBJECTS) multiplication_test.c -o $@ -lgmp -lm
	./test_mul
	@rm -rf test_mul

test_div: $(OBJECTS) division_test.c
	@$(CC) $(OBJECTS) division_test.c -o $@ -lgmp -lm
	./test_div
	@rm -rf test_div

test_float_add: $(OBJECTS) float_addition_test.c
	@$(CC) $(OBJECTS) float_addition_test.c -o $@ -lgmp -lm
	./test_float_add
	@rm -rf test_float_add

%.o: %.c
	@$(CC) -c $< -o $@ -lm

clean:
	$(RM) ../another/*.o \
	../arithmetic/*.o \
	../comparison/*.o \
	../convertion/*.o \
	../core/*.o \
	*out \
	*.o test_add test_sub test_mul test_div test_float_add

rebuild: clean test