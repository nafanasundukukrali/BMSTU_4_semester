#include <stdio.h>
#include <stdint.h>
#include "string_functions.h"

int32_t my_strncpy(char *, const char *, const int32_t);

int main()
{
    printf("%s\n", "=== Пункт 1 ===");

    const char *string = "hahahhlol";
    printf("Входная строка: %s\n", string);
    size_t len = my_strlen(string);
    printf("Длина строки: %zu\n", len);

    const char *string_1 = "";
    printf("Входная строка: %s\n", string_1);
    size_t len_1 = my_strlen(string_1);
    printf("Длина строки: %zu\n", len_1);

    printf("%s\n", "=== Пункт 2 ===");

    char string_out[6];

    const char *string_2 = "bvbaa";
    printf("Входная строка: %s\n", string_2);
    int32_t value = 5;
    my_strncpy(&(string_out[0]), string_2, value);
    printf("Количество копируемых символов: %u, выходная строка: %s\n", value, string_out);

    printf("Входная строка: %s\n", string_2);
    value = 1;
    my_strncpy(&(string_out[0]), string_2, value);
    printf("Количество копируемых символов: %u, выходная строка: %s\n", value, string_out);

    printf("Входная строка: %s\n", string_2);
    value = 0;
    my_strncpy(&(string_out[0]), string_2, value);
    printf("Количество копируемых символов: %u, выходная строка: %s\n", value, string_out);

    return 0;
}
