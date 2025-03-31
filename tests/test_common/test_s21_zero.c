#include "../../decimal_test.h"

START_TEST(test_1_zero) {
  s21_decimal value;
  value.bits[0] = 12345;
  value.bits[1] = 67890;
  value.bits[2] = 54321;
  value.bits[3] = 1;

  s21_zero(&value);
  ck_assert_int_eq(value.bits[0], 0);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST


Suite *create_s21_zero_test(void) {
  Suite *suite = suite_create("s21_decimal_zero");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_1_zero);

  return suite;
}
