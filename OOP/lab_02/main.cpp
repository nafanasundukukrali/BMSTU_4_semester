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


//    Matrix<int> some(3, 3, true);

//    cout << some;


//    Matrix<int> some_1(3, 3, false);

//    cout << some_1;

    for (auto iter = matrix.rbegin(); iter != matrix.rend(); iter++)
        cout << *iter << ' ';

    Matrix<int> matrix_5 = matrix - matrix;
    cout << matrix_5;

    Matrix<int> matrix_9 = {{1, 2}, {3, 4}, {5, 6}};

    Matrix<int> matrix_10 = matrix_1 * matrix_9;

    cout << matrix_10;

//    matrix - matrix_1;

//    matrix + matrix_1;

//    matrix * 5;

    Matrix<float> matrix_r = {{1, 2, 3}, {4, 5, 6}, {7, 8, 8}};

//    matrix_r = matrix_r.inverse();

    cout << endl;
    cout << matrix_r;

    Matrix<int> matrix_f(matrix_r);
    matrix_r = matrix_f;

    cout << endl;
    cout << matrix_f;

    cout << endl;
    cout << matrix_r;

 //   matrix[2][124];

    cout << endl;
    cout << matrix;
    matrix = 5 + matrix;
    cout << endl;
    cout << matrix;

    return 0;
}
