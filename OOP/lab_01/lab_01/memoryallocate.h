#ifndef MEMORYALLOCATE_H
#define MEMORYALLOCATE_H

#include "error.h"
#include <cstdlib>

typedef struct
{
    err_t *return_code;
    size_t one_object_mem_size;
    size_t count;
} params_alocate_function_t;

void* allocate_memory_of_object_array(err_t *return_code, );

#endif // MEMORYALLOCATE_H
