#include "../decimal_test.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = create_s21_zero_test();
  sr = srunner_create(s);

  srunner_add_suite(sr, create_s21_get_sign());
  srunner_add_suite(sr, create_s21_set_sign());

  srunner_add_suite(sr, create_s21_get_scale());
  srunner_add_suite(sr, create_s21_set_scale());

  srunner_set_xml(sr, "./test_output/test_results.xml");
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
