#include <cstdio>

float sin_asm(float dst = 0, bool system = false)
{
    if (!system)
    {
    __asm__(
        "fld %0;"
        "fsin;"
        "fst %0;"
        :"=m"(dst)
        );
    }
    else
    {
    __asm__(
        "fldpi;"
        "fsin;"
        "fst %0;"
        :"=m"(dst)
        );
    }

    return dst;
}

float sin_half_asm(float dst = 0)
{
    float half = 2;

    __asm__(
        "fldpi;"
        "fdiv %1;"
        "fsin\n"
        "fst %0;"
        : "=m"(dst)
        : "m"(half)
        );

    return dst;
}

int main()
{
    printf("%s", "sin(x):\n");
    printf("sin(3.14) = %.20f\n", sin_asm(3.14));
    printf("sin(3.141596) = %.20f\n", sin_asm(3.141596));
    printf("sin(FPU PI) = %.20f\n", sin_asm(0, true));
    printf("%s", "sin(x / 2):\n");
    printf("sin(3.14 / 2) = %.20f\n", sin_asm(3.14 / 2.0));
    printf("sin(3.141596 / 2) = %.20f\n", sin_asm(3.141596 / 2.0));
    printf("sin(FPU PI / 2) = %.20f\n", sin_half_asm());
}
