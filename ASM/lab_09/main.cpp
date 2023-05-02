#include <iostream>
#include <random>

#include "functions.h"

#define TEST_ARRAY_SIZE 9
#define TEST_MATRIX_ELEMENT_COUNT 30

int main()
{
    float v1[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    float v2[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};

    float v3[5][6] {{1, 2, 3, 4, 5, 6},{1, 2, 3, 4, 5, 6},{1, 2, 3, 4, 5, 6},{1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}};
    float v4[5][6] {{1, 2, 3, 4, 5, 6},{1, 2, 3, 4, 5, 6},{1, 2, 3, 4, 5, 6},{1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}};

    std::size_t cx_1 = TEST_ARRAY_SIZE / 8;

    if (TEST_ARRAY_SIZE % 8 != 0) cx_1++;

    sum_vector_asm(v1, v2, 9);

    for (auto &x: v1)
        std::cout << x << ' ';

    std::cout << std::endl;

    return 0;
}
