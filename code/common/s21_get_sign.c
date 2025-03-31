#include "./common.h"

int s21_get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }
