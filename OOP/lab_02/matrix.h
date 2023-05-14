#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include "matrixbase.h"
#include "iterator.h"
#include "const_iterator.h"
#include "exceptionmatrix.h"
#include <cstddef>
#include <ranges>
#include <iostream>
#include <concepts.h>

template<MatrixType T>
class Matrix: public MatrixBase
{
    friend Iterator<T>;
    friend IteratorConst<T>;
public:
    using value_type = T;
    using iterator = Iterator<T>;
    using const_iterator = IteratorConst<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using difference_type = typename iterator::difference_type;
    using reference = typename iterator::reference;
    using const_reference = typename const_iterator::reference;
    using pointer = typename iterator::pointer;
    using const_pointer = typename const_iterator::pointer;

    Matrix() = default;
    explicit Matrix(const size_t rows, const size_t columns);
    Matrix(const size_t rows, const size_t columns, const bool is_unit_matrix);
    explicit Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&matrix) noexcept;
    Matrix(T** array, const size_t rows, const size_t columns);
    template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
    requires std::constructible_from<T, typename std::iterator_traits<Iter>::reference>
    Matrix(const Iter begin, const Iter_e end, const size_t column_size);
    explicit Matrix(FriendlyRange auto range, const size_t column_size);
    Matrix(std::initializer_list<std::initializer_list<T>> list);
    ~Matrix() noexcept = default;

    Matrix<T>& operator = (const Matrix<T>& matrix);
    Matrix<T>& operator = (Matrix<T>& matrix);
    Matrix<T>& operator = (Matrix<T>&& matrix);
    Matrix<T>& operator = (std::initializer_list<std::initializer_list<T>> list);

    template <typename U> requires MatrixEqualityOperationRequires<U>
    bool operator == (const Matrix<U>& matrix) const;
    template <typename U> requires MatrixEqualityOperationRequires<U>
    bool operator != (const Matrix<U>& matrix) const;

    template <typename U> requires MatrixSumOperationRequires<T, U>
    Matrix<T>& operator += (const Matrix<U>& matrix);
    template <typename U> requires MatrixSumOperationRequires<T, U>
    Matrix<T> operator + (const Matrix<U>& matrix) const;
    template <typename U> requires MatrixSumOperationRequires<T, U>
    void sum(const Matrix<U>& matrix);

    template <typename U> requires MatrixSubOperationRequires<T, U>
    Matrix<T>& operator -= (const Matrix<U>& matrix);
    template <typename U> requires MatrixSubOperationRequires<T, U>
    Matrix<T> operator - (const Matrix<U>& matrix) const;
    template <typename U> requires MatrixSubOperationRequires<T, U>
    void sub(const Matrix<U>& matrix);

    template <typename U> requires MatrixMulOperationRequires<T, U>
    Matrix<T>& operator *= (const Matrix<U>& matrix);
    template <typename U> requires MatrixMulOperationRequires<T, U>
    Matrix<T>& operator *= (const U value);
    template <typename U> requires MatrixMulOperationRequires<T, U>
    Matrix<T> operator * (const Matrix<U>& matrix) const;
    template <typename U> requires MatrixMulOperationRequires<T, U>
    Matrix<T> operator * (const U value) const;
    template <typename U> requires MatrixMulOperationRequires<T, U>
    void mul(const Matrix<U>& matrix);
    template <typename U> requires MatrixMulOperationRequires<T, U>
    void mul(const U value);

    template <typename U> requires MatrixDivOperationRequires<T, U>
    Matrix<T>& operator /= (const Matrix<U>& matrix);
    template <typename U> requires MatrixDivOperationRequires<T, U>
    Matrix<T>& operator /= (const U value);
    template <typename U> requires MatrixDivOperationRequires<T, U>
    Matrix<T> operator / (const Matrix<U>& matrix) const;
    template <typename U> requires MatrixDivOperationRequires<T, U>
    Matrix<T> operator / (const U value) const;
    template <typename U> requires MatrixDivOperationRequires<T, U>
    void div(const Matrix<U>& matrix);
    template <typename U> requires MatrixDivOperationRequires<T, U>
    void div(const U value);

    class MatrixRow
    {
        friend Matrix<T>;
    public:
        ~MatrixRow() = default;

        T& operator[](size_t column)
        {
            return this-> _parent._data.get()[column + this->_columns * this->_row_number];
        };

        const T& operator[](size_t column) const
        {
            return this->_parent._data.get()[column + this->_columns * this->_row_number];
        };
    private:
        MatrixRow(const Matrix<T>& parent, size_t row): _parent(parent), _row_number(row), _columns(parent.get_columns_count()) {};
        const Matrix& _parent;
        const size_t _row_number;
        const size_t _columns;
    };

    MatrixRow operator [] (const size_t row);
    MatrixRow operator [] (const size_t row) const;

    T &operator()(size_t row, size_t col);
    const T &operator()(size_t row, size_t col) const;

    bool is_square();
    Matrix<T> transpose();
    bool is_unit() requires MatrixOnlyFloatPointingRequires<T>;
    Matrix<T> inverse() requires MatrixOnlyFloatPointingRequires<T>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator rcbegin() const;
    const_reverse_iterator rcend() const;

    size_t get_rows_count() const;
    size_t size() const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
        for (size_t i = 0; i < matrix.size(); i++)
        {
            std::cout << matrix.begin()[i] << ' ';

            if ((i + 1) % matrix.get_columns_count() == 0)
                std::cout << std::endl;
        }
    }

private:
    std::shared_ptr<T[]> _data = nullptr;
    void _reallocate_data();
    void _check_input_matrix_size_params();
    void _copy_data_from_another_range(auto &range);

    void _check_possibility_to_inverse();
};

#include "matrix.hpp"
#include "matrixrow.hpp"

#endif // MATRIX_H
