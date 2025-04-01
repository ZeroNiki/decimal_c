#ifndef DECIMAL_TEST_H
#define DECIMAL_TEST_H

#include <check.h>
#include <stdlib.h>

#include "./s21_decimal.h"

// Common func
Suite *create_s21_zero_test(void);
Suite *create_s21_get_sign(void);

Suite *create_s21_get_scale(void);
Suite *create_s21_set_scale(void);

#endif // DECIMAL_TEST_H
