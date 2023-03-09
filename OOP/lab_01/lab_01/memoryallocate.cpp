#include "memoryallocate.h"

void* allocate_memory_of_object_array(params_alocate_function_t params)
{
    void *buffer_pointer = malloc(params.one_object_mem_size * params.count);

    if (buffer_pointer == NULL)
        *(params.return_code) = ERROR_ALLOCATE_MEMORY;

    return buffer_pointer;
}
