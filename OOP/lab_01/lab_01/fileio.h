#ifndef FILEIO_H
#define FILEIO_H

#include "error.h"
#include "figure.h"

#define ONE_CORRECT_READ_DATA 1

err_t read_data_from_file(figure_t *figure, char *path);

#endif // FILEIO_H
