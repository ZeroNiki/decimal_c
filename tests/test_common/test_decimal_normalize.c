#include "../../decimal_test.h"

START_TEST(test_val1_lt_val2) {
  // 1234.5
  s21_decimal val1 = {{0x00003039, 0, 0, 0x00010000}};

  // 123.45
  s21_decimal val2 = {{0x00003039, 0, 0, 0x00020000}};

  int old_scale1 = s21_get_scale(val1);
  int old_scale2 = s21_get_scale(val2);

  s21_normalize(&val1, &val2);

  int scale1 = s21_get_scale(val1);
  int scale2 = s21_get_scale(val2);

  ck_assert_int_eq(scale1, scale2);
  ck_assert_int_eq(scale2, old_scale2);
  ck_assert_int_gt(scale1, old_scale1);
}
END_TEST

START_TEST(test_val2_lt_val1) {
  // 123.45
  s21_decimal val1 = {{0x00003039, 0, 0, 0x00020000}};

  // 1234.5
  s21_decimal val2 = {{0x00003039, 0, 0, 0x00010000}};

  int old_scale1 = s21_get_scale(val1);
  int old_scale2 = s21_get_scale(val2);

  s21_normalize(&val1, &val2);

  int scale1 = s21_get_scale(val1);
  int scale2 = s21_get_scale(val2);

  ck_assert_int_eq(scale2, scale1);
  ck_assert_int_eq(scale1, old_scale1);
  ck_assert_int_gt(scale2, old_scale2);
}
END_TEST

START_TEST(test_val1_eq_val2) {
  // 123.45
  s21_decimal val1 = {{0x00003039, 0, 0, 0x00020000}};

  // 123.45
  s21_decimal val2 = {{0x00003039, 0, 0, 0x00020000}};

  int old_scale1 = s21_get_scale(val1);
  int old_scale2 = s21_get_scale(val2);

  s21_normalize(&val1, &val2);

  int scale1 = s21_get_scale(val1);
  int scale2 = s21_get_scale(val2);

  ck_assert_int_eq(scale1, scale2);
  ck_assert_int_eq(scale1, old_scale1);
  ck_assert_int_eq(scale2, old_scale2);
}
END_TEST

Suite *create_s21_normalize(void) {
  Suite *suite = suite_create("s21_decimal_normalize");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_val1_lt_val2);
  tcase_add_test(tc_core, test_val2_lt_val1);
  tcase_add_test(tc_core, test_val1_eq_val2);
  suite_add_tcase(suite, tc_core);

  return suite;
}
