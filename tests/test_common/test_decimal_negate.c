#include "../../decimal_test.h"

// 666
START_TEST(test_positive) {
  s21_decimal num = {{0x0000029A, 0, 0, 0x00000000}};

  s21_negate(&num);
  ck_assert_int_eq(s21_get_sign(num), 1);
}
END_TEST

// -777
START_TEST(test_negative) {
  s21_decimal num = {{0x00000309, 0, 0, 0x80000000}};

  s21_negate(&num);
  ck_assert_int_eq(s21_get_sign(num), 0);
}
END_TEST

// -666.66
START_TEST(test_negative_double) {
  s21_decimal num = {{0x0001046A, 0, 0, 0x80002000}};

  int init_scale = s21_get_scale(num);

  s21_negate(&num);
  ck_assert_int_eq(s21_get_sign(num), 0);
  ck_assert_int_eq(s21_get_scale(num), init_scale);
}
END_TEST

// 777.777
START_TEST(test_positive_double) {
  s21_decimal num = {{0x000BDE31, 0, 0, 0x00003000}};

  int init_scale = s21_get_scale(num);

  s21_negate(&num);
  ck_assert_int_eq(s21_get_sign(num), 1);
  ck_assert_int_eq(s21_get_scale(num), init_scale);
}
END_TEST

Suite *create_s21_negate(void) {
  Suite *suite = suite_create("s21_decimal_negate");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_positive);
  tcase_add_test(tc_core, test_negative);
  tcase_add_test(tc_core, test_positive_double);
  tcase_add_test(tc_core, test_negative_double);
  suite_add_tcase(suite, tc_core);

  return suite;
}
