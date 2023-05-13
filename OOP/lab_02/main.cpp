//#include "testmatrixrow.h"
#include "matrix.h"
#include "matrixrow.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    cout << endl;
    matrix.change_rows(1, 0);

    for (auto &x: matrix)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }

    Matrix<int> matrix_1(matrix);
    vector<int> a {1, 2 ,3};
    vector<int> b(3);

    MatrixRow<float> test_row_1_1 {1, 2, 3};
    MatrixRow<float> test_row_1_2 {3, 2, 2};

    test_row_1_1 += test_row_1_2;
    test_row_1_1 -= test_row_1_2;
    test_row_1_1 *= 5.0;

    for (auto &x: test_row_1_1)
        cout << x;
    cout << endl;

    bool result = test_row_1_1 == test_row_1_2;

    MatrixRow<float> test_row_2 (test_row_1_1.begin(), test_row_1_1.end());

    for (auto &x: test_row_2)
        cout << x;
    cout << endl;
    cout << endl;
    Matrix<float> matrix_4(matrix.begin(), matrix.end());

    for (auto &x: matrix_4)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }

    Matrix<int> some(3, 4);

    for (auto &x: some)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }

//    cout << result << endl;

    Matrix<int> matrix_3 = {{1, 2}, {3, 4}, {5, 6}};

    Matrix<int> matrix_10 = matrix_3 * matrix_1;

//    cout << matrix_4;

    matrix - matrix_1;

    matrix + matrix_1;

    matrix * 5;

    cout << "MATRIX DEF::" << endl;

    for (auto &x: matrix)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }
    cout << endl;

////    cout << endl;
//    matrix.change_columns(0, 2);
////    cout << matrix;


////    cout << endl;
//    matrix.change_rows(1, 0);
////    cout << matrix;

//    cout << endl;
    matrix.add_column(3, {1, 2});
////    cout << matrix;

    for (auto &x: matrix)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }
    cout << endl;

////    cout << endl;
//    matrix.add_row(2, {1, 2, 3, 4});
////    cout << matrix;

////    cout << endl;
    matrix.delete_column(3);
////    cout << matrix;
    for (auto &x: matrix)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }

    cout << endl;

    Matrix<float> matrix_11({{10, -7, 0}, {-3, 6, 2}, {5, -1, 5}});

    Matrix<float> matrix_r = {{1, 2, 3}, {4, 5, 6}, {7, 8, 8}};

    for (auto &x: matrix_r)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }

    cout << endl;

    matrix_r = matrix_r.inverse();

    for (auto &x: matrix_r)
    {
        for (auto &y: x)
            cout << y << ' ';
        cout << endl;
    }

    cout << endl;

//    cout << (matrix_11.calc_determinant()) << endl;
//    cout << endl;
//    matrix.delete_row(1);
////    cout << matrix;

    return 0;
}
