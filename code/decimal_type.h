#ifndef DECIMAL_TYPE_H
#define DECIMAL_TYPE_H

#include <stdint.h>

/* Биты 0-95 хранят значение числа в двоичном виде
 * Биты 96-127 (четвёртый элемент bits[3]):
 * Бит 31 - знак
 * Бит 16-23 степень
 * Остальные биты = 0 */

typedef struct {
  uint32_t bits[4];
} s21_decimal;


#endif // DECIMAL_TYPE_H

