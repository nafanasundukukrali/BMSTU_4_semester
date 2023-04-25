#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include "matrixbase.h"
#include "iterator.h"
#include "const_iterator.h"
#include "matrixrow.h"
#include "exceptionmatrix.h"
#include <cstddef>

template<typename T>
class Matrix: public MatrixBase
{
    friend Iterator<T>;
    friend IteratorConst<T>;
    friend MatrixRow<T>;
public:
    Matrix() = default;
    Matrix(const size_t rows, const size_t columns);
    explicit Matrix(const Matrix &matrix);
    explicit Matrix(Matrix &&matrix);
    explicit Matrix(std::initializer_list<std::initializer_list<T>> list);
    ~Matrix() noexcept = default;

    Matrix<T>& operator = (const Matrix<T>& mtr);
    Matrix<T>& operator = (Matrix<T>&& mtr);
    Matrix<T>& operator = (std::initializer_list<std::initializer_list<T>> list);

    Matrix<T> operator + (const Matrix<T>& matrix) const;
    Matrix<T>& operator += (const Matrix<T>& matrix);
    void add(const Matrix<T>& mtrx) const;

    Matrix<T> operator - (const Matrix<T>& matrix) const;
    Matrix<T>& operator -= (const Matrix<T>& matrix);
    void sub(const Matrix<T>& mtrx) const;

    Matrix<T> operator * (const Matrix<T>& matrix) const;
    Matrix<T>& operator *= (const Matrix<T>& matrix);

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

    Iterator<T> begin();
    Iterator<T> end();
    IteratorConst<T> begin() const;
    IteratorConst<T> end() const;
    IteratorConst<T> cbegin() const;
    IteratorConst<T> cend() const;
    Iterator<T> rbegin();
    Iterator<T> rend();
    IteratorConst<T> rbegin() const;
    IteratorConst<T> rend() const;
    IteratorConst<T> crbegin() const;
    IteratorConst<T> crend() const;

    void fill(Iterator<T> start, const Iterator<T> &end, const T &value);
    void fill(Iterator<T> start, Iterator<T> source_start, const Iterator<T> &source_end);

    // friend std::ostream& operator << (std::ostream& os, const Matrix<T>& mtrx);

private:
    std::shared_ptr<MatrixRow<T>[]> _data = nullptr;

    void _reallocate_data();

    void solve_linear_system_by_gause_method();
    void subtract(Matrix &);
    void summarize(Matrix &);
    void multipy(Matrix &);
};

#include "matrix.hpp"

#endif // MATRIX_H
