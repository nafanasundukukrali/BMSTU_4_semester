#include <stdio.h>
#include <stdint.h>
#include "string_functions.h"

int32_t my_strncpy(char *, const char *, int32_t);

int main()
{
    /*
    int i = 0;


    __asm__ volatile (
        ".intel_syntax noprefix;"
        "mov eax, 5;"
        "mov %0, eax;"
        ".att_syntax;"
        : "=r" (i)
    );

    printf("%d", i);
        */
    /**const char *string = "hahahhlol";
    size_t len = my_strlen(string);
    printf("%zu", len);**/
    char s1[5];
    const char *s2 = "bvbaa";
    int32_t value = 1;
    my_strncpy(&(s1[0]), s2, value);

    printf("%s", s1);

    return 0;
}
