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
    std::string _get_class_name_new() {
        return typeid(*this).name();
    };

    void _validate_empty_new() const {
        if (this->_columns == 0 || this->_rows == 0)
            throw ExceptionEmptyObject(__FILE__, typeid(this).name(), __LINE__);
    };

    void _validate_another_matrix_row_params_new(size_t rows, size_t columns)
    {
        if (this->_rows != rows || this->_columns != columns)
            throw ExceptionIncorrectSrcParams(__FILE__, typeid(*this).name(), __LINE__);
    };

    size_t _rows = 0;
    size_t _columns = 0;
};

#include "matrixbase.hpp"

#endif // MATRIXBASE_H
