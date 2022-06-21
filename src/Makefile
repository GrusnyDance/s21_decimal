CC = gcc

#  УБРАТЬ САНИТАЙЗ ПЕРЕД СДАЧЕЙ

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
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


all: $(TARGET_EXEC)

$(TARGET_EXEC): create_dir $(OBJECTS)
	ar rcs $@ $(OBJ_DIR)/*.o

lib_gcov.a: create_dir $(OBJECTS_GCOV)
	ar rcs $@ $(OBJ_GCOV_DIR)/*.o

create_dir:
	mkdir -p $(OBJ_DIR) $(OBJ_GCOV_DIR)

test: main_tests.c $(HEADER) lib_gcov.a
	$(CC) $(CFLAGS) $^ -o test_test $(LCHECK) $(LDFLAGS) $(GCOV_FLAGS)
	./test_test
	@mv *gcda *gcno $(OBJ_GCOV_DIR)/

gcov_report: test
	@rm -f $(OBJ_GCOV_DIR)/*tests*
	@lcov/bin/./lcov -c -d $(OBJ_GCOV_DIR)/. -o $(OBJ_GCOV_DIR)/coverage.info
	@lcov/bin/./genhtml $(OBJ_GCOV_DIR)/coverage.info --output-directory out

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $(subst /,_,$@) $(LIN_FLAGS)
	@mv *.o $(OBJ_DIR)/

$(OBJ_GCOV_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $(subst /,_,$@) $(LIN_FLAGS)
	@mv *.o *gcno $(OBJ_GCOV_DIR)/

clean:
	$(RM) $(OBJ_DIR) $(OBJ_GCOV_DIR)
	$(RM) $(TARGET_EXEC) lib_gcov.a
	$(RM) *.o *gc* test_test out

lint:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c *.h *.c
	python3 ../materials/linters/cpplint.py --extensions=c \
	./core/*.h ./core/*.c ./another/*.h ./another/*.c \
	./comparison/*.h ./comparison/*.c ./convertion/*.h ./convertion/*.c \
	./arithmetic/*.h ./arithmetic/*.c ./test/*.h ./test/*.c
	$(RM) CPPLINT.cfg

rebuild: clean all

.PHONY: all clean rebuild test lint create_dir gcov_report
	
