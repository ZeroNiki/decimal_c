#include "./common.h"

void s21_zero(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}
