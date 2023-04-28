//#include "testmatrixrow.h"
#include "matrix.h"
#include "matrixrow.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    Matrix<int> matrix {{1, 2, 6}, {3, 4, 5}};
    Matrix<int> matrix_1(matrix);
    vector<int> a {1, 2 ,3};
    vector<int> b(3);
    return 0;
}
