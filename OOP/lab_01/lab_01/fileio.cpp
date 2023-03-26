#include "fileio.h"

static err_t open_file_by_path(FILE **file, char *filePath)
{
    if (filePath == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;
    FILE *buffer_file = NULL;

    buffer_file = fopen(filePath, "r");

    if (buffer_file == NULL || ferror(buffer_file))
    {
        return_code = ERROR_OPEN_FILE;
    }
    else if (feof(buffer_file))
    {
        return_code = ERROR_NO_DATA;
    }

    if (return_code == SUCCESS)
    {
        *file = buffer_file;
    }
    else if (buffer_file != NULL)
    {
        fclose(buffer_file);
    }

    return return_code;
}

err_t read_data_from_file(figure_t *figure, char *path)
{
    if (path == NULL || figure == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    FILE *file = NULL;
    err_t return_code = open_file_by_path(&file, path);

    if (return_code == SUCCESS)
    {
        return_code = read_figure_info_from_file(figure, file);

        if (return_code == SUCCESS && fclose(file))
        {
            return_code = ERROR_CLOSE_FILE;
        }
        else
        {
            return_code = check_figure_correctness(figure);

            if (return_code != SUCCESS)
            {
                free_figure_memory(figure);
            }
        }
    }

    return return_code;
}
