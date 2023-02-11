#include "libarray.h"

short array_left_move(int *array, size_t size, size_t k)
{
    if (array == NULL)
        return ENOMEM;

    short return_code = EXIT_SUCCESS;

    k %= size;
    
    list_queue_t *queue = init_list_queue();

    if (queue == NULL)
        return_code = ENOMEM;

    size_t i = 0;

    for (i = 0; i < k && return_code == EXIT_SUCCESS; i++)
        return_code = list_push(queue, array[i]);

    for (size_t j = 0; i < size && queue->start != NULL && return_code == EXIT_SUCCESS; j++, i++)
    {
        array[j] = array[i];
        array[i] = list_pop(queue);
    }

    list_free_queue(queue);

    return return_code;
}

short check_square(const int value)
{
    int buffer = 1;

    while (buffer < value && buffer * buffer < value)
        buffer++;

    return value != 1 && buffer * buffer == value;
}

void array_get_squares(int *array, size_t size, int *new_array, size_t *new_size)
{
    size_t j = 0;

    for (size_t i = 0; i < size; i++)
        if (array[i] > 0 && check_square(array[i]))
        {
            new_array[j] = array[i];
            j++;
        }

    *new_size = j;
}
