#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include <concepts>

template<typename T, typename U>
concept FloatType = std::floating_point<T> && std::floating_point<U>;

template<typename T, typename U> requires FloatType<T, U>
    void sum_by_cpp(T &dst, const U src)
{
    dst += src;
}

template<typename T, typename U> requires FloatType<T, U>
    void sum_by_asm(T &dst, const U src)
{
    asm (
        "FLD %0;"
        "FADD %1;"
        "FST %0;"
        : "=m" (dst)
        : "m"(src)
        );
}

template<typename T, typename U> requires FloatType<T, U>
    void mul_by_cpp(T &dst, const U src)
{
    dst *= src;
}

template<typename T, typename U> requires FloatType<T, U>
    void mul_by_asm(T &dst, const U src)
{
    asm (
        "FLD %0;"
        "FMUL %1;"
        "FST %0;"
        : "=m" (dst)
        : "m"(src)
        );
}

#endif // TEST_FUNCTIONS_H
