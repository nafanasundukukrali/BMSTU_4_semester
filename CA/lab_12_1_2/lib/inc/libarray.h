#ifndef __LIBARRAY_H__
#define __LIBARRAY_H__

#include <stdlib.h>
#include "queue.h"
#include <errno.h>

short array_left_move(int *array, size_t size, size_t k);
void array_get_squares(int *array, size_t size, int *new_array, size_t *new_size);

#endif
