#include "./common.h"
#include <stdio.h>

void s21_zero(s21_decimal *value) {
  if (value) {
    for (int i = 0; i < 4; i++) {
      value->bits[i] = 0;
    }
  }
}
