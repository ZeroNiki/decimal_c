#include "../decimal_type.h"

int s21_get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }
