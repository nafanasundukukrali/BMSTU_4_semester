#include "../inc/hermite_polynomial.h"

void get_x_multiplicity(double *dst_x, user_data_t *input_data);

int calc_hermite_approximation_coefficients(user_data_t *input_data, polynomial_t *polynomial)
{
    double *buffer_x = malloc(sizeof(double) * input_data->values_count * 2);

    if (buffer_x == NULL)
        return ERROR_DATA_ALLOCATE;

    double *buffer_coefficients = malloc(sizeof(double) * (input_data->n + 1));

    if (buffer_coefficients == NULL)
        return ERROR_DATA_ALLOCATE;

    double *buffer_y = malloc(sizeof(double) * (input_data->n + 1));

    if (buffer_coefficients == NULL)
        return ERROR_DATA_ALLOCATE;
    //memmove(buffer_coefficients, input_data->y + start, sizeof(double) * (input_data->n + 1));
    get_x_multiplicity(buffer_x, input_data);
    
    if (buffer_coefficients == NULL)
        return ERROR_DATA_ALLOCATE;

    size_t start, end;

    double *buffer_pointer = input_data->x;
    input_data->x = buffer_x;

    find_start_and_end_of_approximation_cut(&start, &end, input_data);
    
    // memmove(polynomial->x, input_data->x + start, sizeof(double) * (input_data->n + 1)); 

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

double get_function_value_newton(user_data_t *input_data, polynomial_t *polynomial)
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

void get_x_multiplicity(double *dst_x, user_data_t *input_data)
{
    size_t real_size = 0;
    size_t size = input_data->values_count * 2;

    for (size_t i = 0; i < input_data->values_count; i++)
    {
        dst_x[real_size] = input_data->x[i];
        real_size++;

        size_t derivatives = 0;
        node_t *buffer = input_data->y_derivative[i];

        while (buffer != NULL) 
        {
            derivatives++;
            buffer = buffer->next;
        }

        if (real_size + derivatives < size)
        {
            dst_x = realloc(dst_x, size * 2 * sizeof(double));
            
            if (dst_x == NULL)
            {
                free(dst_x);

                return;
            }

            size *= 2;
        }


        buffer = input_data->y_derivative[i];

        while (buffer != NULL) 
        {
            dst_x[real_size] = buffer->node;
            buffer = buffer->next;
            real_size++;
        }
    }
}
