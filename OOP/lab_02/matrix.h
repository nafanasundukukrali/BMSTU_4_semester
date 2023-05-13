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
#include <iostream>
#include <concepts.h>

template<MatrixType T>
class Matrix: public MatrixBase
{
    friend Iterator<Matrix, T, MatrixRow<T>>;
    friend IteratorConst<Matrix, T, MatrixRow<T>>;
public:
    explicit Matrix() = default;
    Matrix(const size_t rows, const size_t columns, const bool is_unit_matrix = false);
    explicit Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&matrix) noexcept;
    Matrix(T** array, const size_t rows, const size_t columns);
    template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
    requires std::constructible_from<MatrixRow<T>, typename std::iterator_traits<Iter>::reference>
    Matrix(const Iter begin, const Iter_e end);

    Matrix(std::initializer_list<std::initializer_list<T>> list);
    ~Matrix() noexcept = default;

    Matrix<T>& operator = (const Matrix<T>& matrix);
    Matrix<T>& operator = (Matrix<T>& matrix);
    Matrix<T>& operator = (Matrix<T>&& matrix);
    Matrix<T>& operator = (std::initializer_list<std::initializer_list<T>> list);

    bool operator == (const Matrix<T>& matrix) const;
    bool operator != (const Matrix<T>& matrix) const;

    Matrix<T>& operator += (const Matrix<T>& matrix);
    Matrix<T> operator + (const Matrix<T>& matrix) const;

    Matrix<T>& operator -= (const Matrix<T>& matrix);
    Matrix<T> operator - (const Matrix<T>& matrix);

    Matrix<T>& operator *= (const Matrix<T>& matrix);
    Matrix<T>& operator *= (const T value);
    Matrix<T> operator * (const Matrix<T>& matrix);
    Matrix<T> operator * (const T value);

    Matrix<T>& operator /= (const Matrix<T>& matrix);
    Matrix<T>& operator /= (const T value);
    Matrix<T> operator / (const Matrix<T>& matrix);
    Matrix<T> operator / (const T value);

    MatrixRow<T>& operator [] (const size_t row);
    const MatrixRow<T>& operator [] (const size_t row) const;
    T &operator()(size_t row, size_t col);
    const T &operator()(size_t row, size_t col) const;

    Matrix<T> sum(const Matrix<T>& matrix);

    Matrix<T> sub(const Matrix<T>& matrix);

    Matrix<T> mul(const Matrix<T>& matrix);
    Matrix<T> mul(const T value);

    Matrix<T> div(const Matrix<T>& matrix);
    Matrix<T> div(const T value);

    bool is_square();
    bool is_unit();
    Matrix<T> transpose();
    Matrix<T> inverse();

    void change_columns(size_t from_position, size_t to_position);
    void change_rows(size_t from_position, size_t to_position);
    void add_column(size_t post_column_number, std::initializer_list<T> list);
    void add_row(size_t post_row_number, std::initializer_list<T> list);
    void delete_column(size_t column_number);
    void delete_row(size_t row_number);

    Iterator<Matrix, T, MatrixRow<T>> begin();
    Iterator<Matrix, T, MatrixRow<T>> end();
    IteratorConst<Matrix, T, MatrixRow<T>> begin() const;
    IteratorConst<Matrix, T, MatrixRow<T>> end() const;
    IteratorConst<Matrix, T, MatrixRow<T>> cbegin() const;
    IteratorConst<Matrix, T, MatrixRow<T>> cend() const;

    size_t get_rows_count() const;
    IteratorConst<Matrix, T, MatrixRow<T>> size() const;
private:
    std::shared_ptr<MatrixRow<T>[]> _data = nullptr;
    void _reallocate_data();
    void _check_input_matrix_size_params();
    void _copy_data_from_another_range(auto &range);

    T _calc_determinant();
};

#include "matrix.hpp"

#endif // MATRIX_H
