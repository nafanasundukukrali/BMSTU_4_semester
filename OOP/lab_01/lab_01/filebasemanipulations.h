#ifndef FILE_BASE_MANIPULATIONS_H
#define FILE_BASE_MANIPULATIONS_H
#include <cstdio>
#include "error.h"

#define ONE_CORRECT_READ_DATA 1

err_t read_size_t_number_from_file(size_t *number, FILE *file);


#endif // FILE_BASE_MANIPULATIONS_H
