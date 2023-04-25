#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include <cstddef>

class MatrixBase
{
public:
    MatrixBase(size_t rows = 0, size_t columns = 0) noexcept: _rows(rows), _columns(columns) {};

    virtual ~MatrixBase() = default;

    size_t get_rows_count() const { return this->_rows; };
    size_t get_columns_count() const { return this->_columns; };
protected:
    size_t _rows = 0;
    size_t _columns = 0;
};

#include "matrixbase.hpp"

#endif // MATRIXBASE_H
