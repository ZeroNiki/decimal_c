#include "../../decimal_test.h"

START_TEST(test_negative) {
  s21_decimal num = {{0x00000005, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_get_sign(num), 1);
}
END_TEST

Suite *create_s21_get_sign(void) {
  Suite *suite = suite_create("s21_decimal_get_sign");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_negative);
  suite_add_tcase(suite, tc_core);

  return suite;
}
