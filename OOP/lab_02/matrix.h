#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include "matrixbase.h"
#include "iterator.h"
#include "const_iterator.h"
#include "matrixrow.h"
#include "exceptionmatrix.h"
#include <cstddef>
#include <ranges>

template<typename T>
class Matrix: public MatrixBase
{
    friend Iterator<Matrix, T>;
    friend IteratorConst<Matrix, T>;
public:
    explicit Matrix() = default;
    Matrix(const size_t rows, const size_t columns);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix);
    Matrix(std::initializer_list<std::initializer_list<T>> list);
    ~Matrix() noexcept = default;

    Matrix<T>& operator = (const Matrix<T>& matrix);
    Matrix<T>& operator = (Matrix<T>&& matrix);
    Matrix<T>& operator = (std::initializer_list<std::initializer_list<T>> list);



    bool operator == (const Matrix& matrix) const;
    bool operator != (const Matrix& matrix) const;

    void change_columns(size_t from_position, size_t to_position);
    void change_rows(size_t from_position, size_t to_position);
    void add_column(size_t previously_column_number, std::initializer_list<std::initializer_list<T>> list);
    void add_row(size_t previosly_row_number, std::initializer_list<std::initializer_list<T>> list);
    void delete_column(size_t column_number);
    void delete_row(size_t row_number);

    bool is_zero() const;
    bool is_square() const;

    Matrix &transpose();

    Iterator< Matrix, MatrixRow<T>> begin();
    Iterator< Matrix, MatrixRow<T>> end();
    IteratorConst<Matrix, MatrixRow<T>> begin() const;
    IteratorConst<Matrix, MatrixRow<T>> end() const;
    IteratorConst<Matrix, MatrixRow<T>> cbegin() const;
    IteratorConst<Matrix, MatrixRow<T>> cend() const;
    Iterator< Matrix, MatrixRow<T>> rbegin();
    Iterator< Matrix, MatrixRow<T>> rend();
    IteratorConst<Matrix, MatrixRow<T>> rbegin() const;
    IteratorConst<Matrix, MatrixRow<T>> rend() const;
    IteratorConst<Matrix, MatrixRow<T>> crbegin() const;
    IteratorConst<Matrix, MatrixRow<T>> crend() const;

    void fill(Iterator<Matrix, MatrixRow<T>> start, const Iterator<Matrix, MatrixRow<T>> &end, const T &value);
    void fill(Iterator<Matrix, MatrixRow<T>> start, Iterator<Matrix, MatrixRow<T>> source_start, const Iterator<Matrix, MatrixRow<T>> &source_end);

    // friend std::ostream& operator << (std::ostream& os, const Matrix<T>& mtrx);

private:
    std::shared_ptr<MatrixRow<T>[]> _data = nullptr;
    void _reallocate_data();
    void _check_input_matrix_size_params();
};

//static_assert(std::ranges::bidirectional_range<Matrix<int>>);

#include "matrix.hpp"

#endif // MATRIX_H
