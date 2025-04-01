#include "../../decimal_test.h"

// 12.34
START_TEST(test_1) {
  s21_decimal num = {{0x000004D2, 0, 0, 0x00020000}};
  ck_assert_int_eq(s21_get_scale(num), 2);
}
END_TEST

// 5.100
START_TEST(test_2) {
  s21_decimal num = {{0x000013EC, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_get_scale(num), 3);
}
END_TEST

// 4.1
START_TEST(test_3) {
  s21_decimal num = {{0x00000029, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_get_scale(num), 1);
}
END_TEST

// 10
START_TEST(test_4) {
  s21_decimal num = {{0x00000A, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_get_scale(num), 0);
}
END_TEST

Suite *create_s21_get_scale(void) {
  Suite *suite = suite_create("s21_decimal_get_scale");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  suite_add_tcase(suite, tc_core);

  return suite;
}
