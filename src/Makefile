CC = gcc

#  УБРАТЬ САНИТАЙЗ ПЕРЕД СДАЧЕЙ

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -fprofile-arcs --coverage
LCHECK = -lcheck -lgmp
LIN_FLAGS := -lpthread -pthread -lrt -lm -lsubunit
ifeq ($(shell uname), Linux)
LCHECK += $(LIN_FLAGS)
endif

SOURCES:= core/bit.c \
	core/sign.c \
	core/shift.c \
	core/exponent.c \
	core/debug.c \
	core/decimal.c \
	another/s21_floor.c \
	another/s21_truncate.c \
	another/balancing.c \
	another/bank_round.c \
	another/s21_neg.c \
	another/s21_round.c \
	comparison/s21_eq.c \
	comparison/s21_less.c \
	comparison/s21_gr.c \
	comparison/s21_gr_or_eq.c \
	comparison/s21_not_eq.c \
	comparison/s21_less_or_eq.c \
	convertion/int_to_dec.c \
	convertion/float_to_dec.c \
	convertion/dec_to_float.c \
	convertion/dec_to_int.c \
	convertion/shared.c \
	arithmetic/add.c \
	arithmetic/sub.c \
	arithmetic/mul.c \
	arithmetic/div.c \
	arithmetic/fmod.c \

OBJ_DIR := ./obj
OBJ_GCOV_DIR := ./obj_gcov
OBJECTS := $(addprefix obj/,$(SOURCES:.c=.o))
OBJECTS_GCOV := $(addprefix obj_gcov/,$(SOURCES:.c=.o))
HEADER = s21_decimal.h

TARGET_EXEC := s21_decimal.a

RM := rm -rf

.PHONY: all clean rebuild test

all: $(TARGET_EXEC)

$(TARGET_EXEC): create_dir $(OBJECTS)
	ar rcs $@ $(OBJ_DIR)/*.o

create_dir:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $(subst /,_,$@)
	@mv *.o $(OBJ_DIR)/

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(TARGET_EXEC)
	$(RM) *.o
	
