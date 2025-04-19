AR = ar rcs
CC = gcc
CFLAG = -Wall -Wextra -Werror -pedantic -std=c11
GCOV_FLAG = --coverage -fprofile-arcs -ftest-coverage -lgcov
LIBFLAG = -lcheck -lm -lrt -lsubunit
COVRFLG = --html --html-details --exclude-lines-by-pattern '.*assert.*' --exclude '.*test_.*' --exclude '.*run.c*'

CODE_DIR = ./code
TEST_DIR = ./tests
OBJ_DIR = ./object
TEST_OUT = ./test_output

CODE_SRC = $(shell find ./code -name '*.c')
CODE_OBJ = $(patsubst $(CODE_DIR)/%.c, $(OBJ_DIR)/%.o, $(CODE_SRC))
CODE_GCOV_OBJ = $(patsubst $(CODE_DIR)/%.c, $(OBJ_DIR)/%.gcov.o, $(CODE_SRC))

TEST_SRC = $(shell find ./tests -name '*.c')

LIBRARY = s21_decimal.a
GCOV_LIB = test_s21_decimal.a

EXEC = run_tests
GCOV_EXEC = gcov_tests

# ------ Main targets ------
all: $(LIBRARY)

test: $(EXEC)
	./$(EXEC)

gcov_exec: clean $(GCOV_EXEC)
	./$(GCOV_EXEC)

gcov_report: gcov_exec
	mkdir gcov-rep
	mkdir lcov-rep
	lcov --capture --directory . --output-file lcov-rep/cov.info
	genhtml lcov-rep/cov.info --output-directory lcov-rep
	python3 -m venv venv
	. venv/bin/activate && pip install gcovr
	. venv/bin/activate && gcovr --root . $(COVRFLG) --output gcov-rep/report.html && deactivate
	rm -rf ./venv/

clean:
	rm -rf $(OBJ_DIR) $(LIBRARY) $(EXEC)
	rm -rf $(GCOV_LIB) $(GCOV_EXEC)
	rm -rf gcov-rep lcov-rep
	rm -f gcov_tests-*
	rm -rf test_output

# ------ Libs ------
$(LIBRARY): $(CODE_OBJ)
	$(AR) $@ $^

$(GCOV_LIB): $(CODE_GCOV_OBJ)
	$(AR) $@ $^

# ------ Execs ------
$(EXEC): $(TEST_SRC) $(LIBRARY)
	mkdir -p $(TEST_OUT)
	$(CC) $(CFLAG) -I. $^ -o $@ $(LIBFLAG)

$(GCOV_EXEC): $(TEST_SRC) $(GCOV_LIB)
	mkdir -p $(TEST_OUT)
	$(CC) $(CFLAG) $(GCOV_FLAG) -I. $^ -o $@ $(LIBFLAG)

# ------ Objects ------
$(OBJ_DIR)/%.o: $(CODE_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

# ------ GCOV Objects ------
$(OBJ_DIR)/%.gcov.o: $(CODE_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAG) $(GCOV_FLAG) -c $< -o $@

# ----- Valgrind ------
valgrind: $(EXEC)
	valgrind --leak-check=full --track-origins=yes --log-file=test_output/memcheck.log ./$(EXEC)

.PHONY: all test clean $(LIBRARY) gcov_report gcov_exec
