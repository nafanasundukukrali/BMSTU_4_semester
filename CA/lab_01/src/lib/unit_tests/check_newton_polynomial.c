#include "unit_tests.h"
#include <stdio.h>

START_TEST(test_x_not_in_input_data)
{
    double x[] = {-0.50, -0.25, 0.0, 0.25, 0.50, 0.75, 1.0};
    double y[] = {0.707, 0.924, 1.0, 0.924, 0.707, 0.383, 0};
    user_data_t input_data = {false, &(x[0]), &(y[0]), NULL, 0.6, 7, 4, 4};
    double coefficients[] = {0, 0, 0, 0, 0};
    double new_x[] = {0, 0, 0, 0, 0};
    double *p1 = (double *)coefficients;
    double *p2 = (double *)new_x;

    polynomial_t result = {p1, p2};

    double stamp[] = {1, -0.304, -1.128, 0.363, 0.149};

    calc_newton_approximation_coefficients(&input_data, &result);

    for (size_t i = 0; i < input_data.n; i++)
        ck_assert(fabs(coefficients[i] - stamp[i]) < EPSILON);

    double result_value = get_function_value_newton(&input_data, &result);

    ck_assert(fabs(result_value - 0.589) < EPSILON);
}
END_TEST

START_TEST(test_x_not_in_cut)
{
    double x[] = {1.0, 2.0};
    double y[] = {1.0, 2.0};
    user_data_t input_data = {false, &(x[0]), &(y[0]), NULL, -1.0, 2, 1, 0};
    double coefficients[] = {0, 0};
    double new_x[] = {0, 0};
    double *p1 = (double *)coefficients;
    double *p2 = (double *)new_x;

    polynomial_t result = {p1, p2};

    double stamp[] = {1, 1};

    calc_newton_approximation_coefficients(&input_data, &result);

    for (size_t i = 0; i < input_data.n; i++)
        ck_assert(fabs(coefficients[i] - stamp[i]) < EPSILON);

    double result_value = get_function_value_newton(&input_data, &result);
    ck_assert(fabs(result_value + 1) < EPSILON);
}
END_TEST

START_TEST(test_x_after_cut)
{
    double x[] = {1.0, 2.0};
    double y[] = {1.0, 2.0};
    user_data_t input_data = {false, &(x[0]), &(y[0]), NULL, 10.0, 2, 1, 0};
    double coefficients[] = {0, 0};
    double new_x[] = {0, 0};
    double *p1 = (double *)coefficients;
    double *p2 = (double *)new_x;

    polynomial_t result = {p1, p2};

    double stamp[] = {1, 1};

    calc_newton_approximation_coefficients(&input_data, &result);

    for (size_t i = 0; i < input_data.n; i++)
        ck_assert(fabs(coefficients[i] - stamp[i]) < EPSILON);

    double result_value = get_function_value_newton(&input_data, &result);
    ck_assert(fabs(result_value - 10) < EPSILON);
}


START_TEST(test_x_cut_value)
{
    double x[] = {1.0, 2.0};
    double y[] = {1.0, 2.0};
    user_data_t input_data = {false, &(x[0]), &(y[0]), NULL, 1, 2, 1, 0};
    double coefficients[] = {0, 0};
    double new_x[] = {0, 0};
    double *p1 = (double *)coefficients;
    double *p2 = (double *)new_x;

    polynomial_t result = {p1, p2};

    double stamp[] = {1, 1};

    calc_newton_approximation_coefficients(&input_data, &result);

    for (size_t i = 0; i < input_data.n; i++)
        ck_assert(fabs(coefficients[i] - stamp[i]) < EPSILON);

    double result_value = get_function_value_newton(&input_data, &result);
    ck_assert(fabs(result_value - 1) < EPSILON);
}

Suite *newton_polynomial_suite(Suite *suite)
{
    TCase *pos_test_case;

    pos_test_case = tcase_create("positives");

    tcase_add_test(pos_test_case, test_x_not_in_input_data);
    tcase_add_test(pos_test_case, test_x_not_in_cut);
    tcase_add_test(pos_test_case, test_x_after_cut);
    tcase_add_test(pos_test_case, test_x_cut_value);
//    tcase_add_test(pos_test_case, test_one_square);
//    tcase_add_test(pos_test_case, test_all_squares);
//    tcase_add_test(pos_test_case, test_less_zero);
    
    suite_add_tcase(suite, pos_test_case);

    return suite;
}
