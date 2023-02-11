#include "../inc/newton_polynomial.h"

int calc_herm
/*
void find_start_and_end_of_approximation_cut(size_t *start, size_t *end, user_data_t *input_data);

int calc_newton_approximation_coefficients(user_data_t *input_data, newton_polynomial_t *polynomial)
{
    size_t start, end;

    find_start_and_end_of_approximation_cut(&start, &end, input_data);
    
    double *buffer_coefficients = malloc(sizeof(double) * (input_data->n + 1));

    if (buffer_coefficients == NULL)
        return ERROR_DATA_ALLOCATE;

    memmove(buffer_coefficients, input_data->y + start, sizeof(double) * (input_data->n + 1)); 
    memmove(polynomial->x, input_data->x + start, sizeof(double) * (input_data->n + 1)); 

    size_t step = 1;
    double last_result, pre_last_result;

    while (start + step < end)
    {
        last_result = buffer_coefficients[step-1];

        for (size_t i = step; i + start < end; i++)
        {
            pre_last_result = buffer_coefficients[i];
            buffer_coefficients[i] = ((buffer_coefficients[i] - last_result)/
                (input_data->x[start + i] - input_data->x[start + i - step]));
            last_result = pre_last_result;
        }
        
        step++;
    }

    memmove(polynomial->coefficients, buffer_coefficients, sizeof(double) * (input_data->n + 1));

    free(buffer_coefficients);

    return EXIT_SUCCESS;
}

double get_function_value_newton(user_data_t *input_data, newton_polynomial_t *polynomial)
{
    double result = 0, coefficient = 1;

    result += polynomial->coefficients[0];

    for (size_t i = 1; i < input_data->n + 1; i++)
    {
        coefficient *= input_data->search_x - polynomial->x[i - 1];
        result += coefficient * polynomial->coefficients[i];
    }

    return result;
}

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
*/
