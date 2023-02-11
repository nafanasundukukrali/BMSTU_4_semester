#include "unit_tests.h"
#include <check.h>
#include <stddef.h>
#include <stdlib.h>

START_TEST(test_triangle_matrix)
{
    matrix_t first_matrix;

    first_matrix.matrix = NULL;

    first_matrix.matrix = calloc(3, sizeof(double *));

    first_matrix.matrix[0] = calloc(4, sizeof(double));
    first_matrix.matrix[1] = calloc(4, sizeof(double));
    first_matrix.matrix[2] = calloc(4, sizeof(double));

    first_matrix.matrix[0][0] = 1;
    first_matrix.matrix[0][1] = 2;
    first_matrix.matrix[0][2] = 3;
    first_matrix.matrix[0][3] = 4;
    first_matrix.matrix[1][0] = 1;
    first_matrix.matrix[1][1] = 3;
    first_matrix.matrix[1][2] = 3;
    first_matrix.matrix[1][3] = 4;
    first_matrix.matrix[2][0] = 0;
    first_matrix.matrix[2][1] = 0;
    first_matrix.matrix[2][2] = 1;
    first_matrix.matrix[2][3] = 4;

    first_matrix.rows = 3;
    first_matrix.columns = 4;

    double tmp[] = {-8, 0, 4};
    double result[] = {0, 0, 0};
    double *p = (double *)result;

    int result_value = solve_linear_system_by_gausse_method(&first_matrix, p);
    
    ck_assert_int_eq(result_value, EXIT_SUCCESS);

    DBG_PRINT_MATRIX(first_matrix.matrix, first_matrix.rows, first_matrix.columns);
    
    for (size_t i = 0; i < first_matrix.rows; i++)
        ck_assert(fabs(tmp[i] - result[i]) < EPSILON);

    for (size_t i = 0; i < first_matrix.rows; i++)
        free(first_matrix.matrix[i]);

    free(first_matrix.matrix);
}
END_TEST

/*

START_TEST(test_all_squares)
{
    int data[] = {4, 9, 36, 16, 49}, test[5], result[] = {4, 9, 36, 16, 49};
    size_t size;

    array_get_squares(data, 5, test, &size);

    ck_assert_mem_eq(test, result, sizeof(int) * 5);
}
END_TEST

START_TEST(test_less_zero)
{
    int data[] = {4, -9, 36, -16, 49}, test[5], result[] = {4, 36, 49};
    size_t size;

    array_get_squares(data, 5, test, &size);

    ck_assert_mem_eq(test, result, sizeof(int) * 3);
}
END_TEST
*/

Suite *matrix_suite(Suite *suite)
{
    TCase *pos_test_case;

    pos_test_case = tcase_create("positives");

    tcase_add_test(pos_test_case, test_triangle_matrix);
//    tcase_add_test(pos_test_case, test_one_square);
//    tcase_add_test(pos_test_case, test_all_squares);
//    tcase_add_test(pos_test_case, test_less_zero);
    
    suite_add_tcase(suite, pos_test_case);

    return suite;
}
