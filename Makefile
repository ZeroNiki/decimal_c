AR = ar rcs
CC = gcc
CFLAG = -Wall -Wextra -Werror -pedantic -std=c11
LIBFLAG = -lcheck -lm -lpthread -lrt -lsubunit

CODE_DIR = ./code
TEST_DIR = ./tests
OBJ_DIR = ./object

CODE_SRC = $(wildcard $(CODE_DIR)/*/*.c)
CODE_OBJ = $(patsubst $(CODE_DIR)/%.c, $(OBJ_DIR)/%.o, $(CODE_SRC))

TEST_SRC = $(wildcard $(TEST_DIR)/*/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRC))
TEST_OBJ += $(OBJ_DIR)/run.o

LIBRARY = s21_decimal.a
EXEC = run_tests

all: $(LIBRARY)

$(LIBRARY): $(CODE_OBJ)
	$(AR) $@ $^

$(OBJ_DIR)/%.o: $(CODE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

$(OBJ_DIR)/run.o: $(TEST_DIR)/run.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

$(EXEC): $(TEST_OBJ) $(LIBRARY)
	$(CC) $(CFLAG) $^ -o $@ $(LIBFLAG)

test: $(EXEC)
	@./$(EXEC)

clean:
	rm -rf $(OBJ_DIR) $(LIBRARY) $(EXEC)

.PHONY: all test clean $(LIBRARY)
