#include "stdio.h"
#include "stdlib.h"
#include "unit_tests.h"

START_TEST(test_move_zero)
{
    int test[3] = {1, 2, 3}, result[3] = {1, 2, 3};

    array_left_move(test, 3, 0);
    
    ck_assert_mem_eq(test, result, sizeof(int) * 3);
}
END_TEST 

START_TEST(test_move_len)
{
    int test[3] = {1, 2, 3}, result[3] = {1, 2, 3};

    array_left_move(test, 3, 3);

    ck_assert_mem_eq(test, result, sizeof(int) * 3);
}
END_TEST 

START_TEST(test_move_one_to_one)
{
    int test[1] = {1}, result[1] = {1};

    array_left_move(test, 1, 10);

    ck_assert_mem_eq(test, result, sizeof(int));
}
END_TEST 

START_TEST(test_move_five_to_tree)
{
    int test[5] = {1, 2, 3, 4 ,5}, result[5] = {4, 5, 1, 2, 3};

    array_left_move(test, 5, 3);

    ck_assert_mem_eq(test, result, sizeof(int));
}
END_TEST 

START_TEST(test_move_five_to_fourteen)
{
    int test[5] = {1, 2, 3, 4 ,5}, result[5] = {5, 1, 2, 3, 4};

    array_left_move(test, 5, 14);

    ck_assert_mem_eq(test, result, sizeof(int));
}
END_TEST 

Suite *array_left_move_suite(Suite *suite)
{
    TCase *pos_test_case;

    pos_test_case = tcase_create("positives");

    tcase_add_test(pos_test_case, test_move_one_to_one);
    tcase_add_test(pos_test_case, test_move_zero);
    tcase_add_test(pos_test_case, test_move_len);
    tcase_add_test(pos_test_case, test_move_five_to_tree);
    tcase_add_test(pos_test_case, test_move_five_to_fourteen);
    
    suite_add_tcase(suite, pos_test_case);

    return suite;
}
