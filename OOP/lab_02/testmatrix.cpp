#include "testmatrix.h"
#include "matrix.h"

void TestMatrix::base_constructor()
{
    Matrix<int> matrix;
    QVERIFY(matrix.get_columns_count() == 0 && matrix.get_rows_count() == 0);
}

void TestMatrix::copy_constructor()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> matrix_1(matrix);

    QVERIFY(matrix == matrix_1);
}

void TestMatrix::sum_matrix()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> matrix_1(matrix);
    Matrix<int> result = matrix + matrix_1;
    Matrix<int> real_res {{2, 4, 12}, {6, 8, 10}};

    QVERIFY(result == real_res);
}

void TestMatrix::sub_matrix()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> matrix_1 = matrix;
    Matrix<int> result = matrix - matrix_1;
    Matrix<int> real_res {{0, 0, 0}, {0, 0, 0}};

    QVERIFY(result == real_res);
}

void TestMatrix::mul_matrix()
{
    Matrix<int> matrix_1 {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> matrix_3 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix<int> result = matrix_1 * matrix_3;
    Matrix<int> real_res {{37, 46}, {40, 52}};

    QVERIFY(result == real_res);
}

void TestMatrix::mul_matrix_2()
{
    Matrix<int> matrix_1 {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> matrix_3 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix<int> result = matrix_3 * matrix_1;
    Matrix<int> real_res {{7, 10, 16}, {15, 22, 38}, {23, 34, 60}};

    QVERIFY(result == real_res);
}

void TestMatrix::mul_number()
{
    Matrix<int> matrix_1 {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> result = matrix_1 * 5;
    Matrix<int> real_res {{5, 10, 30}, {15, 20, 25}};

    QVERIFY(result == real_res);
}

void TestMatrix::change_columns()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    matrix.change_columns(0, 2);
    Matrix<int> real_res {{6, 2, 1}, {5, 4, 3}};

    QVERIFY(matrix == real_res);
}

void TestMatrix::change_rows()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}, {7, 8, 9}};
    matrix.change_rows(0, 2);
    Matrix<int> real_res {{7, 8, 9}, {3, 4, 5}, {1, 2, 6}};

    QVERIFY(matrix == real_res);
}

void TestMatrix::add_column()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}, {7, 8, 9}};
    matrix.add_column(3, {1, 2, 4});
    Matrix<int> real_res {{1, 2, 6, 1}, {3, 4, 5, 2}, {7, 8, 9, 4}};

    QVERIFY(matrix == real_res);
}

void TestMatrix::add_row()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}, {7, 8, 9}};
    matrix.add_row(1, {1, 2, 4});
    Matrix<int> real_res {{1, 2, 6}, {1, 2, 4}, {3, 4, 5}, {7, 8, 9}};

    QVERIFY(matrix == real_res);
}

void TestMatrix::delete_column()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}, {7, 8, 9}};
    matrix.delete_column(1);
    Matrix<int> real_res {{1, 6}, {3, 5}, {7, 9}};

    QVERIFY(matrix == real_res);
}

void TestMatrix::delete_row()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}, {7, 8, 9}};
    matrix.delete_row(1);
    Matrix<int> real_res {{1, 2, 6}, {7, 8, 9}};

    QVERIFY(matrix == real_res);
}

void TestMatrix::get_matrix_element()
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}, {7, 8, 9}};
    int value = matrix[1][2];

    QVERIFY(value == 5);
}

QTEST_MAIN(TestMatrix)
