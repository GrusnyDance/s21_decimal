CC = gcc

CFLAGS = -lm
CFLAGS += -Wall -Wextra -Werror -g -fsanitize=address

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

BUILD_DIR := ./build
OBJECTS:= $(SOURCES:%=$(BUILD_DIR)/%.o)

TARGET_EXEC := s21_decimal.a

RM:= rm -rf

.PHONY: all
all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJECTS)
	ar rcs $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)
	rm -f $(TARGET_EXEC)
