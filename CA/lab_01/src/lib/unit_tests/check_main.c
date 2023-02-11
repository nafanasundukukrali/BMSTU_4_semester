#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "unit_tests.h"

int main(void)
{
    Suite *suite;
    SRunner *runner;
    int no_failed = 0;

    suite = suite_create("all_suite");

    newton_polynomial_suite(suite);
    matrix_suite(suite);
    runner = srunner_create(suite);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
