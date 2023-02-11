#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <math.h>
#include "consts.h"
#include <stddef.h>

#define ERROR_SOLVE_LS 31

typedef struct {
    double **matrix;
    size_t rows;
    size_t columns;
} matrix_t;

int solve_linear_system_by_gausse_method(matrix_t *matrix, double *result);

#endif
