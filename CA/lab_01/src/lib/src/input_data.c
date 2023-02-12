#include "../inc/input_data.h"

void find_start_and_end_of_approximation_cut(size_t *start, size_t *end, user_data_t *input_data)
{
    size_t left = input_data->search_x_position;
    size_t right = input_data->search_x_position + 1;

    size_t i = 0;

    while (i < input_data->n)
    {
        if (left > 0)
        {
            left--;
            i++;
        }

        if (i < input_data->n && right < input_data->values_count)
        {
            right++; 
            i++;
        }
    }

    *start = left;
    *end = right;
}
