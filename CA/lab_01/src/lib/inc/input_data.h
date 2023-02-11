#ifndef __USER_DATA_H__
#define __USER_DATA_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool inX; // Флаг, если x в массиве входных данных
    double *x; 
    double *y;
    double *y_derivative;
    double search_x; // х для интерполяции
    size_t values_count; // количество строк в исходной таблице
    size_t n; // степень многочлена
    size_t search_x_position; // позиция x для интерполяции, не больше x
} user_data_t;

#endif
