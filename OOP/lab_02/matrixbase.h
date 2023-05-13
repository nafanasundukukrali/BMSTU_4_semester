#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include <cstddef>
#include <exceptionmatrix.h>
#include <typeinfo>

class MatrixBase
{
public:
    explicit MatrixBase(size_t rows = 0, size_t columns = 0): _rows(rows), _columns(columns) {};
    virtual ~MatrixBase() = default;
    virtual size_t get_rows_count() const = 0;
    size_t get_columns_count() const { return this->_columns; };
protected:
    void _validate_empty(size_t line) const {
        if (this->_columns == 0 || this->_rows == 0)
            throw ExceptionEmptyObject(__FILE__, line);
    };

    void _validate_another_matrix_params(size_t rows, size_t columns, size_t line)
    {
        if (this->_rows != rows || this->_columns != columns)
            throw ExceptionIncorrectSrcParams(__FILE__, line);
    };

    void _validate_input_pointer(void *pointer, size_t line)
    {
        if (pointer == NULL)
            throw ExceptionNullObjectPointer(__FILE__, line);
    }

    size_t _rows = 0;
    size_t _columns = 0;
};

#include "matrixbase.hpp"

#endif // MATRIXBASE_H
