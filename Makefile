## Loading
# Colors
GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

# Logger
define PRINT
	@printf "$(BLUE)==>$(NC) $(YELLOW)%s$(NC)\n" "$(1)"
endef

define ERR
	@printf "$(BLUE)==>$(NC) $(RED)%s$(NC)\n" "$(1)"
endef

# ------ Loading logger -------
define LOADING
	@bash -c '\
		source scripts/anim.sh && \
		trap BLA::stop_loading_animation SIGINT && \
		BLA::start_loading_animation "$${BLA_modern_metro[@]}"; \
		sleep 1.2; \
		{ $(1); } &> /dev/null; \
		BLA::stop_loading_animation \
	'
endef

# ----- Main -----
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
	@./$(EXEC)

gcov_exec: clean $(GCOV_EXEC)
	@./$(GCOV_EXEC)

gcov_report: gcov_exec
	$(call PRINT, "Generating\ coverage\ report...")
	@mkdir -p gcov-rep lcov-rep
	$(call LOADING, lcov --capture --directory . --output-file lcov-rep/cov.info)
	$(call LOADING, genhtml lcov-rep/cov.info --output-directory lcov-rep)
	$(call LOADING, python3 -m venv venv)
	$(call LOADING, . venv/bin/activate && pip install gcovr)
	$(call LOADING, . venv/bin/activate && gcovr --root . $(COVRFLG) --output gcov-rep/report.html && deactivate)
	@rm -rf ./venv/
	@echo "$(GREEN)✔ Coverage report generated: gcov-rep/report.html$(NC)"

clean:
	$(call ERR, "Deleting\ garbage...")
	$(call LOADING, rm -rf $(OBJ_DIR) $(LIBRARY) $(EXEC) $(GCOV_LIB) $(GCOV_EXEC))
	$(call LOADING, rm -rf gcov-rep lcov-rep gcov_tests-* test_output)
	@echo "$(GREEN)✔ Garbage was deleted!$(NC)"

# ------ Libs ------
$(LIBRARY): $(CODE_OBJ)
	$(call PRINT, "Create\ lib...")
	$(call LOADING, $(AR) $@ $^)
	@echo "$(GREEN)✔ Lib $(LIBRARY) built!$(NC)"

$(GCOV_LIB): $(CODE_GCOV_OBJ)
	$(call PRINT, "Create\ lib\ for\ gcov...")
	$(call LOADING, $(AR) $@ $^)
	@echo "$(GREEN)✔ Lib $(GCOV_LIB) built!$(NC)"

# ------ Execs ------
$(EXEC): $(TEST_SRC) $(LIBRARY)
	$(call PRINT, "Create\ executable\ file...")
	@mkdir -p $(TEST_OUT)
	$(call LOADING, $(CC) $(CFLAG) -I. $^ -o $@ $(LIBFLAG))
	@echo "$(GREEN)✔ $(EXEC) was created!$(NC)"

$(GCOV_EXEC): $(TEST_SRC) $(GCOV_LIB)
	$(call PRINT, "Create\ executable\ file\ for\ gcov...")
	@mkdir -p $(TEST_OUT)
	$(call LOADING, $(CC) $(CFLAG) $(GCOV_FLAG) -I. $^ -o $@ $(LIBFLAG))
	@echo "$(GREEN)✔ $(GCOV_EXEC) was created!$(NC)"

# ------ Objects ------
$(OBJ_DIR)/%.o: $(CODE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call LOADING, $(CC) $(CFLAG) -c $< -o $@)
	@echo "$(GREEN)✔ Obj file created: $@$(NC)"

# ------ GCOV Objects ------
$(OBJ_DIR)/%.gcov.o: $(CODE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call LOADING, $(CC) $(CFLAG) $(GCOV_FLAG) -c $< -o $@)
	@echo "$(GREEN)✔ Obj file created: $@$(NC)"

# ----- Valgrind ------
valgrind: $(EXEC)
	$(call PRINT, "Running\ Valgrind\ memory\ check...")
	$(call LOADING, valgrind --leak-check=full --track-origins=yes --log-file=$(TEST_OUT)/memcheck.log ./$(EXEC))
	@echo "$(GREEN)✔ Valgrind check complete. Log: $(TEST_OUT)/memcheck.log $(NC)"

# ---- Clang-format -----
clang-format:
	$(call PRINT, "Running\ Clang-Format...")
	$(call LOADING, clang-format --style=Google -i $(CODE_SRC) $(TEST_SRC))
	@clang-format --style=Google -n $(CODE_SRC) $(TEST_SRC)
	@echo "$(GREEN)✔ Clang-format complete!$(NC)"

format-check:
	$(call PRINT, "Running\ format\ check...")
	$(call LOADING, @clang-format --style=Google -n $(CODE_SRC) $(TEST_SRC))
	@echo "$(GREEN)✔ Format check complete!$(NC)"

# ---- Cppcheck ------
cppcheck:
	$(call PRINT, "Running\ format\ check...")
	@mkdir -p $(TEST_OUT)
	$(call LOADING, cppcheck --enable=all --inconclusive --std=c11 --language=c $(CODE_SRC) $(TEST_SRC) 2> $(TEST_OUT)/cppcheck.log)
	@echo "$(GREEN)✔ Cppcheck complete. Log: $(TEST_OUT)/cppcheck.log$(NC)"

# ------ Full check -------
full-check: format-check valgrind cppcheck

.PHONY: all test clean $(LIBRARY) gcov_report gcov_exec
