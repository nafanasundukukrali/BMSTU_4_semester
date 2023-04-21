#include "string_functions.h"

size_t my_strlen(const char *string)
{
    size_t len = 0 ;

    asm (
        ".intel_syntax noprefix;"
        "mov ecx, -1;"
        "mov edi, %1;"
        "xor al, al;"
        "repne scasb;"
        "not ecx;"
        "dec ecx;"
        "mov %0, ecx;"
        ".att_syntax;"
        : "=r" (len)
        : "r" (string)
        : "eax", "ecx", "edi"
    );

    return len;
}
