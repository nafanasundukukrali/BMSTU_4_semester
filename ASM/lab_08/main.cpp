#include <sys/time.h>
#include <cstdio>
#include <random>
#include "test_functions.h"

#ifndef COUNT
#define COUNT 5
#endif

#define ERROR_INCORRECT_COUNT_INPUT -1
#define ERROR_FILE_OPEN -2

template<typename T, typename U> requires FloatType<T, U>
    long timer_for_func(T& dst, const U src, void (*func)(T&, const U))
{
    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    func(dst, src);

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);

    return end.tv_nsec - start.tv_nsec;
}

template<typename T>
float randomFloat()
{
    return (T)(rand()) / (T)(RAND_MAX);
}

int main()
{
    FILE *file = fopen("results.txt", "w");

    if (!file)
    {
        printf("%s", "ERROR: CAN'T OPEN RESULT FILE!");

        return ERROR_FILE_OPEN;
    }

    fprintf(file, "%s", "float float sum cpp\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        float dst = randomFloat<float>();
        float src = randomFloat<float>();

        void (*func)(float&, float) = sum_by_cpp;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "float float sum asm\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        float dst = randomFloat<float>();
        float src = randomFloat<float>();

        void (*func)(float&, float) = sum_by_asm;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "float float mul cpp\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        float dst = randomFloat<float>();
        float src = randomFloat<float>();

        void (*func)(float&, float) = mul_by_cpp;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "float float mul asm\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        float dst = randomFloat<float>();
        float src = randomFloat<float>();

        void (*func)(float&, float) = mul_by_asm;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "double double sum cpp\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        double dst = randomFloat<double>();
        double src = randomFloat<double>();

        void (*func)(double&, double) = sum_by_cpp;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "double double sum asm\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        double dst = randomFloat<double>();
        double src = randomFloat<double>();

        void (*func)(double&, double) = sum_by_asm;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "double double mul cpp\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        double dst = randomFloat<double>();
        double src = randomFloat<double>();

        void (*func)(double&, double) = mul_by_cpp;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fprintf(file, "%s", "double double mul asm\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        double dst = randomFloat<double>();
        double src = randomFloat<double>();

        void (*func)(double&, double) = mul_by_asm;
        long result = timer_for_func(dst, src, func);
        fprintf(file, "%ld\n", result);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
