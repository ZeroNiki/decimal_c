#include "common.h"

void s21_normalize(s21_decimal *value1, s21_decimal *value2) {
  int scale1 = s21_get_scale(*value1);
  int scale2 = s21_get_scale(*value2);

  if (scale1 < scale2) {
    s21_set_scale(value1, scale2);
  } else if (scale1 > scale2) {
    s21_set_scale(value2, scale1);
  }
}
