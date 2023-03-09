#ifndef FILEIO_H
#define FILEIO_H

#include "error.h"
#include "figure.h"
#include "memoryallocate.h"

#define ONE_CORRECT_READ_DATA 1

err_t open_file_by_path(char *filePath, FILE **file);
err_t read_data_from_file(FILE *file, figure_t *figure);

#endif // FILEIO_H
