//#include "testmatrixrow.h"
#include "matrix.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    for (auto &x: matrix)
        cout << x << ' ';
    cout << endl;

    Matrix<int> matrix_1(matrix);

    for (auto &x: matrix)
        cout << x << ' ';

    cout << endl;

    Matrix<int> matrix_2(matrix.begin(), matrix.end(), 3);

    for (auto &x: matrix_2)
        cout << x << ' ';

    cout << endl;

    vector<int> a = {1, 2 ,3, 4, 5, 6};
    a.begin();

    Matrix<int> matrix_3(a, 3);

    for (auto &x: matrix_3)
        cout << x << ' ';

    cout << endl;

    cout << (matrix == matrix_1);

    cout << endl;


    Matrix<int> some(3, 3, true);

    cout << some;


    Matrix<int> some_1(3, 3, false);

    cout << some_1;

    for (auto iter = matrix.rbegin(); iter != matrix.rend(); iter++)
        cout << *iter << ' ';

    Matrix<int> matrix_5 = matrix - matrix;
    cout << matrix_5;

//    cout << result << endl;

    Matrix<int> matrix_9 = {{1, 2}, {3, 4}, {5, 6}};

    Matrix<int> matrix_10 = matrix_1 * matrix_9;

    cout << matrix_10;

//    matrix - matrix_1;

//    matrix + matrix_1;

//    matrix * 5;

//    cout << "MATRIX DEF::" << endl;

//    for (auto &x: matrix)
//    {
//        for (auto &y: x)
//            cout << y << ' ';
//        cout << endl;
//    }
//    cout << endl;

////    cout << endl;
//    matrix.change_columns(0, 2);
////    cout << matrix;


////    cout << endl;
//    matrix.change_rows(1, 0);
////    cout << matrix;

//    cout << endl;
//    matrix.add_column(3, {1, 2});
////    cout << matrix;

//    for (auto &x: matrix)
//    {
//        for (auto &y: x)
//            cout << y << ' ';
//        cout << endl;
//    }
//    cout << endl;

////    cout << endl;
//    matrix.add_row(2, {1, 2, 3, 4});
////    cout << matrix;

////    cout << endl;
//    matrix.delete_column(3);
////    cout << matrix;
//    for (auto &x: matrix)
//    {
//        for (auto &y: x)
//            cout << y << ' ';
//        cout << endl;
//    }

//    cout << endl;

//    Matrix<float> matrix_11({{10, -7, 0}, {-3, 6, 2}, {5, -1, 5}});

    Matrix<float> matrix_r = {{1, 2, 3}, {4, 5, 6}, {7, 8, 8}};

//    for (auto &x: matrix_r)
//    {
//        for (auto &y: x)
//            cout << y << ' ';
//        cout << endl;
//    }

//    cout << endl;


    matrix_r = matrix_r.inverse();

    cout << endl;
    cout << matrix_r;

//    for (auto &x: matrix_r)
//    {
//        for (auto &y: x)
//            cout << y << ' ';
//        cout << endl;
//    }

//    cout << endl;

//    cout << (matrix_11.calc_determinant()) << endl;
//    cout << endl;
//    matrix.delete_row(1);
////    cout << matrix;

    return 0;
}
