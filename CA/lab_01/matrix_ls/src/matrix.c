#include "../inc/matrix.h"

void make_matrix_upper_triangular(matrix_t *matrix);
void free_matrix(matrix_t **matrix);
matrix_t *allocate_new_matrix(size_t rows,size_t columns);
void copy_matrix(matrix_t *dst, matrix_t *source);

int solve_linear_system_by_gausse_method(matrix_t *matrix, double *result)
{
    matrix_t *matrix_copy = allocate_new_matrix(matrix->rows, matrix->columns);
    
    if (matrix_copy == NULL)
        return ERROR_SOLVE_LS;
    
    copy_matrix(matrix_copy, matrix);

    make_matrix_upper_triangular(matrix_copy);

    for (size_t i = matrix_copy->rows - 1; i + 1 > 0; i--)
        for (size_t j = matrix_copy->columns - 2; j > i; j--)
            matrix_copy->matrix[i][matrix_copy->columns - 1] -= matrix_copy->matrix[j][(
                matrix_copy->columns - 1)] * matrix_copy->matrix[i][j];
    
    for (size_t i = 0; i < matrix_copy->rows; i++)
        result[i] = matrix_copy->matrix[i][matrix_copy->columns - 1];
    
    free_matrix(&matrix_copy);

    return EXIT_SUCCESS;
}

void copy_matrix(matrix_t *dst, matrix_t *source)
{
    for (size_t i = 0; i < source->rows; i++)
        for (size_t j = 0; j < source->columns; j++)
            dst->matrix[i][j] = source->matrix[i][j];
}


matrix_t *allocate_new_matrix(size_t rows,size_t columns)
{
    matrix_t *new_matrix = malloc(sizeof(matrix_t));
    
    if (new_matrix == NULL)
        return NULL;

    new_matrix->columns = columns;
    new_matrix->rows = 0;

    new_matrix->matrix = malloc(sizeof(double *) * rows);
    
    if (new_matrix->matrix == NULL)
    {
        free_matrix(&new_matrix);

        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        new_matrix->matrix[i] = malloc(new_matrix->columns * sizeof(double)); 
        
        if (new_matrix->matrix[i] == NULL)
        {
            free_matrix(&new_matrix);

            return new_matrix;
        }

        new_matrix->rows++;
    }

    return new_matrix;
}

void free_matrix(matrix_t **matrix)
{
    for (size_t i = 0; i < (*matrix)->rows; i++)
        free((*matrix)->matrix[i]);
    
    free((*matrix)->matrix);
    free(*matrix);

    *matrix = NULL;
}

void make_matrix_upper_triangular(matrix_t *matrix)
{
    for (size_t k = 0; k < matrix->rows; k++)
    {
        for (size_t i = k; i < matrix->rows; i++)
            for (size_t j = matrix->columns - 1; 
                    j + 1 > k && fabs(matrix->matrix[i][k]) > EPSILON; j--)
                matrix->matrix[i][j] /= matrix->matrix[i][k]; 

        for (size_t i = k + 1; i < matrix->rows; i++)
            for (size_t j = matrix->columns - 1; j >= k && 
                    fabs(matrix->matrix[i][k]) > EPSILON; j--)
                matrix->matrix[i][j] -= matrix->matrix[k][j]; 
    }
}
