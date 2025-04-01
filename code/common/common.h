#ifndef COMMON_H
#define COMMON_H

#include "../decimal_type.h"

void s21_zero(s21_decimal *value);

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);

int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);

void s21_negate(s21_decimal *value);
void s21_normalize(s21_decimal *value1, s21_decimal *value2);

// int s21_get_bit(s21_decimal value, int index);

#endif // COMMON_H
