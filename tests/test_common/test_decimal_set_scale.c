#include "../../decimal_test.h"

START_TEST(test_scale_simple) {
  s21_decimal num = {0};

  s21_set_scale(&num, 0);
  ck_assert_int_eq(s21_get_scale(num), 0);
}
END_TEST

START_TEST(test_scale_middle) {
  s21_decimal num = {0};

  s21_set_scale(&num, 50);
  ck_assert_int_eq(s21_get_scale(num), 50);
}
END_TEST

START_TEST(test_scale_big_num) {
  s21_decimal num = {0};

  s21_set_scale(&num, 28);
  ck_assert_int_eq(s21_get_scale(num), 28);
}
END_TEST

START_TEST(test_scale_edge) {
  s21_decimal num = {{0x00000501, 0, 0, 0x00002000}};

  s21_set_scale(&num, 1);
  ck_assert_int_eq(s21_get_scale(num), 1);
}
END_TEST

Suite *create_s21_set_scale(void) {
  Suite *suite = suite_create("s21_decimal_set_scale");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_scale_simple);
  tcase_add_test(tc_core, test_scale_middle);
  tcase_add_test(tc_core, test_scale_big_num);
  tcase_add_test(tc_core, test_scale_edge);
  suite_add_tcase(suite, tc_core);

  return suite;
}
