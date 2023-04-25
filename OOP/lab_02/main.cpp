//#include "testmatrixrow.h"
#include "matrix.h"
#include "matrixrow.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    size_t r = 6, c = 6;
    Matrix<int> matrix {{1, 2}, {3, 4}};
    Matrix<int> matrix_1(matrix);
    return 0;
}
