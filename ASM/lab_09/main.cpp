#include <iostream>
#include <random>
#include <memory>
#include <ctime>
#include <iostream>

#ifndef TEST_COUNT
#define TEST_COUNT 10
#endif

#ifndef TEST_ARRAY_SIZE
#define TEST_ARRAY_SIZE 21
#endif

#define ERROR_INCORRECT_COUNT_INPUT -1
#define ERROR_FILE_OPEN -2

long timer_for_func(double (&v_1)[TEST_ARRAY_SIZE], double (&v_2)[TEST_ARRAY_SIZE],
                    const size_t size,
                    void (*func)(double (&v_1)[TEST_ARRAY_SIZE], double (&v_2)[TEST_ARRAY_SIZE], const std::size_t size))
{
    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    func(v_1, v_2, size);

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);

    return end.tv_nsec - start.tv_nsec;
}

std::size_t calculate_cx(const std::size_t size)
{
    std::size_t cx = size / 4;

    if (size % 4 != 0)
        cx++;

    return cx;
}

void sum_vector_cpp(double (&v_1)[TEST_ARRAY_SIZE], double (&v_2)[TEST_ARRAY_SIZE], const std::size_t size)
{
    for (std::size_t i = 0; i < size; i++)
        v_1[i] *= v_2[i];
}

void sum_vector_asm(double (&v_1)[TEST_ARRAY_SIZE], double (&v_2)[TEST_ARRAY_SIZE], const std::size_t size)
{
    std::size_t new_size = calculate_cx(size);

    asm (
        "mov rcx, %2 \n\t"
        "mov rsi, 0 \n\t"
        "reader_1:\n\t"
        "vmovupd ymm0, [%0 + rsi] \n\t"
        "vmovupd ymm1, [%1 + rsi]  \n\t"
        "vmulpd ymm2, ymm1, ymm0 \n\t"
        "vmovupd [%0 + rsi], ymm2 \n\t"
        "push rax\n\t"
        "mov rax, 32 \n\t"
        "add rsi, rax \n\t"
        "pop rax\n\t"
        "loop reader_1 \n\t"
        : "=m" (v_1)
        : "m" (v_2), "r"(new_size)
        : "rcx", "rsi","ymm0", "ymm1", "ymm2"
        );
}

int main()
{
    double v1[TEST_ARRAY_SIZE];
    double a = 1;
    double v2[TEST_ARRAY_SIZE];
    double b = 1;

    FILE *file = fopen("results.txt", "w");

    size_t step = TEST_ARRAY_SIZE / 10;

    if (!file)
    {
        printf("%s", "ERROR: CAN'T OPEN RESULT FILE!");

        return ERROR_FILE_OPEN;
    }

    fprintf(file, "%s", "double vector mul cpp\n");

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        for (std::size_t i = 0; i < TEST_ARRAY_SIZE; i++)
        {
            v1[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            v2[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }

        size_t test_size = TEST_ARRAY_SIZE / 10;

        void (*func)(double (&)[TEST_ARRAY_SIZE], double (&)[TEST_ARRAY_SIZE], const std::size_t) = sum_vector_cpp;

        for (size_t i = 1; i < TEST_ARRAY_SIZE; i+=step)
        {
            long result = timer_for_func(v1, v2, i, func);

            fprintf(file, "%ld\n", result);
        }
    }

    fprintf(file, "%s", "double vector mul asm\n");

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        for (std::size_t i = 0; i < TEST_ARRAY_SIZE; i++)
        {
            v1[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            v2[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }

        void (*func)(double (&)[TEST_ARRAY_SIZE], double (&)[TEST_ARRAY_SIZE], const std::size_t) = sum_vector_asm;

        for (size_t i = 1; i < TEST_ARRAY_SIZE; i+=step)
        {
            long result = timer_for_func(v1, v2, i, func);

            fprintf(file, "%ld\n", result);
        }
    }

    std::cout << b;

    return 0;
}
