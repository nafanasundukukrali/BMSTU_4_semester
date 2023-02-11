#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#ifdef DEBUG
    #define DBG_PRINT(s, ...) printf(s, __VA_ARGS__)
    #define DBG_PRINT_MATRIX(matrix, rows, columns)               \
        do                                                        \
        {                                                         \
            printf("matrix in case: %s\n", __func__);             \
            for (size_t i = 0; i < rows; i++)                     \
            {                                                     \
                for (size_t j = 0; j < columns; j++)              \
                    printf("%lf ", matrix[i][j]);                 \
                printf("\n");                                     \
            }                                                     \
        } while(0)                                                
#else
    #define DBG_PRINT(s, ...) ((void) 0)
    #define DBG_PRINT_MATRIX(matrix, rows, columns) ((void) 0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include "../inc/matrix.h"
#include <check.h>
#include <math.h>
#include <stdint.h>

Suite *matrix_suite(Suite *suite);

#endif
