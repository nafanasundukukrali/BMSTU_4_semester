#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <concepts>

std::size_t calculate_cx(const std::size_t size)
{
    std::size_t cx = size / 8;

    if (size % 8 != 0 && size > 8)
        cx++;

    return cx;
}

template<typename T>
concept FloatType = std::floating_point<T> || std::integral<T>;

template<typename T> requires FloatType<T>
    void sum_vector_cpp(T*v_1, T*v_2, const std::size_t size)
{
    for (std::size_t i = 0; i < size; i++)
        v_1[i] *= v_2[i];
}

template<typename T> requires FloatType<T>
    void sum_vector_asm(T*v_1, T*v_2, const std::size_t size)
{
    std::size_t new_size = calculate_cx(size);

    asm (
        "mov rcx, %2 \n\t"
        "mov rsi, 0 \n\t"
        "reader_1:\n\t"
        "vmovups ymm0, [%0 + rsi] \n\t"
        "vmovups ymm1, [%1 + rsi]  \n\t"
        "vmulps ymm2, ymm1, ymm0 \n\t"
        "vmovups [%0 + rsi], ymm2 \n\t"
        "mov rax, 8 \n\t"
        "add rsi, rax \n\t"
        "loop reader_1 \n\t"
        : "=m" (v_1)
        : "m" (v_2), "r"(new_size)
        : "rcx", "rsi"
        );
}

#endif // FUNCTIONS_H
