#include "unit_tests.h"

START_TEST(test_zero_squares)
{
    int test[] = {1, 2, 3};
    size_t size;

    array_get_squares(test, 3, NULL, &size);

    ck_assert_int_eq(size, 0);
}
END_TEST

START_TEST(test_one_square)
{
    int data[] = {1, 11, 12, 16, 3}, test[5], result[] = {16};
    size_t size;

    array_get_squares(data, 5, test, &size);

    ck_assert_mem_eq(test, result, sizeof(int) * 1);
}
END_TEST

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

Suite *array_get_squares_suite(Suite *suite)
{
    TCase *pos_test_case;

    pos_test_case = tcase_create("positives");

    tcase_add_test(pos_test_case, test_zero_squares);
    tcase_add_test(pos_test_case, test_one_square);
    tcase_add_test(pos_test_case, test_all_squares);
    tcase_add_test(pos_test_case, test_less_zero);
    
    suite_add_tcase(suite, pos_test_case);

    return suite;
}
