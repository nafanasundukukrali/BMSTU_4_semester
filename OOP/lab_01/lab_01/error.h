#ifndef ERROR_H
#define ERROR_H

#include <QMessageBox>

enum error_codes {
    SUCCESS,
    ERROR_READ_DATA,
    ERROR_UNCORRECT_PARAMS,
    ERROR_OPEN_FILE,
    ERROR_NO_DATA,
    ERROR_NO_PATH,
    ERROR_CLOSE_FILE,
    ERROR_ALLOCATE_MEMORY,
    ERROR_INCORRECT_EDGE_INFO,
    ERROR_NO_LOADED_FIGURE,
    ERROR_GLOBAL_WINDOW_PARAMS_NOT_SET,
    ERROR_COPY_FIGURE
};

typedef enum error_codes err_t;

void displayErrorMessage(const int error_type);

#endif // ERROR_H