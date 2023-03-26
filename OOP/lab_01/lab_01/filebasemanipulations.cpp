#include "filebasemanipulations.h"

err_t read_size_t_number_from_file(size_t *number, FILE *file)
{
    if (file == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;
    long long buffer_count;

    if (fscanf(file, "%lld", &buffer_count) != ONE_CORRECT_READ_DATA &&
            buffer_count >= 0)
    {
        return_code = ERROR_READ_DATA;
    }
    else
    {
        *number = (size_t)buffer_count;
    }

    return return_code;
}
