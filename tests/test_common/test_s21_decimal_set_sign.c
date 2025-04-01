#include "../../decimal_test.h"

START_TEST(set_sign_negative) {
  s21_decimal num = {0};

  s21_set_sign(&num, 1);
  ck_assert_int_eq(s21_get_sign(num), 1);
}
END_TEST

START_TEST(set_sign_possitive) {
  s21_decimal num = {0};

  s21_set_sign(&num, 0);
  ck_assert_int_eq(s21_get_sign(num), 0);
}
END_TEST

// -12.4
START_TEST(set_sign_change) {
  s21_decimal num = {{0x0000007C, 0, 0, 0x80001000}};

  // 12.4
  s21_set_sign(&num, 0);
  ck_assert_int_eq(s21_get_sign(num), 0);

  // -12.4
  s21_set_sign(&num, 1);
  ck_assert_int_eq(s21_get_sign(num), 1);
}
END_TEST


Suite *create_s21_set_sign(void) {
  Suite *suite = suite_create("s21_decimal_set_scale");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, set_sign_possitive);
  tcase_add_test(tc_core, set_sign_negative);
  tcase_add_test(tc_core, set_sign_change);
  suite_add_tcase(suite, tc_core);

  return suite;
}
