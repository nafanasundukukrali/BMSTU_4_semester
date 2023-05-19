#include <ranges>
#include <concepts>
#include <numeric>
#include <algorithm>
#include "matrix.h"
#include "exceptionmatrix.h"

template<MatrixType T>
Matrix<T>::Matrix(const size_t rows, const size_t columns): MatrixBase(rows, columns)
{
    if (rows == 0 || columns == 0)
        throw ExceptionOutOfIndex(__FILE__,  __LINE__, "Matrix params incorrect.");

    this->_reallocate_data();
}

template<MatrixType T>
Matrix<T>::Matrix(const Matrix<T> &matrix): MatrixBase(matrix._rows, matrix._columns)
{
    this->_reallocate_data();

    std::ranges::copy(matrix.begin(), matrix.end(), (*this).begin());
}

template<MatrixType T>
template<MatrixType U>
Matrix<T>::Matrix(const Matrix<U> &matrix) requires FriendlyMatrixType<T, U>: MatrixBase(matrix.get_rows_count(), matrix.get_columns_count())
{
    this->_reallocate_data();

    std::ranges::copy(matrix.begin(), matrix.end(), (*this).begin());
}

template<MatrixType T>
template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
requires std::constructible_from<T, typename std::iterator_traits<Iter>::reference>
Matrix<T>::Matrix(const Iter begin, const Iter_e end, const size_t column_size): MatrixBase()
{
    size_t size_rows = 0;

    for (auto iter = begin; iter != end; iter++, size_rows++);

    if (size_rows == 0 || size_rows % column_size != 0)
        ExceptionIncorrectSourceSizeParams(__FILE__, __LINE__, "Incorrect column_size param");

    this->_columns = column_size;
    this->_rows = size_rows / column_size;
    this->_reallocate_data();

    std::ranges::copy(begin, end, this->begin());
}

template<MatrixType T>
Matrix<T>::Matrix(FriendlyRange auto range, const size_t column_size): MatrixBase()
{
    size_t size_rows = 0;

    for (auto iter = std::begin(range); iter != std::end(range); iter++, size_rows++);

    if (size_rows == 0 || size_rows % column_size != 0)
        ExceptionIncorrectSourceSizeParams(__FILE__, __LINE__, "Incorrect column_size param");

    this->_columns = column_size;
    this->_rows = size_rows / column_size;
    this->_reallocate_data();

    std::ranges::copy(std::begin(range), std::end(range), this->begin());
}

template<MatrixType T>
template <typename Container> requires FriendlyContainer<T, Container>
Matrix<T>::Matrix(const Container &container): MatrixBase(container.get_rows_count(), container.get_columns_count())
{
    this->_reallocate_data();

    std::ranges::copy(std::begin(container), std::end(container), this->begin());
}

template<MatrixType T>
Matrix<T>::Matrix(Matrix<T> &&matrix) noexcept: MatrixBase(matrix._rows, matrix._columns)
{
    this->_data = matrix._data;
}

template<MatrixType T>
Matrix<T>::Matrix(T** array, const size_t rows, const size_t columns): MatrixBase(rows, columns)
{
    this->_validate_input_pointer(array);
    this->_reallocate_data();

    size_t i = 0;

    for (auto &row: *this)
        row = array[i];
}

template<MatrixType T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list): MatrixBase(list.size(), list.begin()->size())
{
    this->_reallocate_data();

    size_t i = 0;

    this->_copy_data_from_another_range(list);
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;

    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        std::ranges::copy(matrix._data[i].begin(), matrix._data[i].end(), this->_data[i].begin());

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;
    this->_data = matrix._data;

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;

    this->_reallocate_data();

    std::ranges::copy(matrix.begin(), matrix.end(), this->begin());

    return *this;
}

template<MatrixType T>
template<MatrixType U>
Matrix<T>& Matrix<T>::operator = (const Matrix<U>& matrix)
{
    this->_rows = matrix.get_rows_count();
    this->_columns = matrix.get_columns_count();

    this->_reallocate_data();

    std::ranges::copy(matrix.begin(), matrix.end(), this->begin());

    return *this;
}

template<MatrixType T>
template <typename Container> requires FriendlyContainer<T, Container>
Matrix<T>& Matrix<T>::operator = (const Container& matrix)
{
    this->_rows = matrix.get_rows_count();
    this->_columns = matrix.get_columns_count();

    this->_reallocate_data();

    std::ranges::copy(matrix.begin(), matrix.end(), this->begin());

    return *this;
}

template<MatrixType T>
Matrix<T> &Matrix<T>::make_unit() requires MatrixOnlyFloatPointingRequires<T>
{
    if (!this->is_square())
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "This matrix is not square, transposition is not availiable.");

    Matrix<T> buffer(this->_rows, this->_columns);

    std::ranges::for_each(*this, [] (auto &element) {element = 0;});

    for (size_t i = 0; i < this->_columns; i++) (*this)[i][i] = 1;

    return buffer;
}

template<MatrixType T>
bool Matrix<T>::is_square()
{
    return this->_columns == this->_rows && this->_rows != 0;
}

template<MatrixType T>
bool Matrix<T>::is_unit() requires MatrixOnlyFloatPointingRequires<T>
{
    if (!this->is_square())
        return false;

    for (size_t i = 0; i < this->_columns; i++)
        for (size_t j = 0; j < this->_columns; j++)
            if ((*this)[i][j] != (*this)[i][j] ||
                i != j && (*this)[i][j] != 0 ||
                i == j && (*this)[i][j] == 0)
                return false;

    return true;
}

template<MatrixType T>
Matrix<T> &Matrix<T>::transpose()
{
    Matrix<T> buffer(this->_columns, this->_rows);

    for (size_t i = 0; i < this->_columns; i++)
        for (size_t j = i + 1; j < this->_rows; j++)
            std::swap(buffer[i][j], (*this)[j][i]);

    return buffer;
}

template<MatrixType T>
T Matrix<T>::get_det() requires MatrixOnlyFloatPointingRequires<T>
{
    Matrix<T> U(*this);
    Matrix<T> L(this->_rows, this->_columns);

    for (size_t i = 0; i < this->_columns; i++)
        for (size_t j = i; j < this->_columns; j++)
            if (U[i][i] != 0)
                L[j][i]=U[j][i]/U[i][i];
            else
                ExceptionImpossibleToDivide(__FILE__, __LINE__);

    for(size_t k = 1; k < this->_columns; k++)
    {
        for(size_t i = k-1; i < this->_columns; i++)
            for(size_t j = i; j < this->_columns; j++)
                if (U[i][i] != 0)
                    L[j][i]=U[j][i]/U[i][i];
                else
                    ExceptionImpossibleToDivide(__FILE__, __LINE__);

        for(size_t i = k; i < this->_columns; i++)
            for(size_t j = k-1; j < this->_columns; j++)
                U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j];
    }

    T prov = U[0][0];

    for (size_t i = 1; i < this->_columns; i++)
        prov *= U[i][i];

    return prov;
}

template<MatrixType T>
Matrix<T> &Matrix<T>::inverse() requires MatrixOnlyFloatPointingRequires<T>
{
    this->_check_possibility_to_inverse();

    Matrix<T> buffer(*this), result(this->_columns, this->_columns, true);

    for (size_t j = 0; j < this->_columns; j++) {
        if (buffer[j][j] == 0)
        {
            size_t k = j;

            for (; k < this->_columns && buffer[j][k] == 0; k++);

            std::swap_ranges(buffer.begin() + j * this->_columns, buffer.begin() + (j + 1) * this->_columns,
                             buffer.begin() + k * this->_columns);
        }

        T divide = buffer[j][j];

        std::for_each_n(buffer.begin() + j * _columns, buffer._columns, [divide] (auto &x) {x /= divide;});
        std::for_each_n(result.begin() + j * _columns, result._columns, [divide] (auto &x) {x /= divide;});

        for (size_t i = 0; i < this->_columns; i++) {
            if (i == j) continue;

            T buf_1 = buffer[i][j];

            for (size_t k = 0; k < this->_columns; k++) {
                buffer[i][k] -= buf_1 * buffer[j][k];
                result[i][k] -= buf_1 * result[j][k];
            }
        }
    }

    return result;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (std::initializer_list<std::initializer_list<T>> list)
{
    this->_rows = list.size();
    this->_rows = list.begin->size();

    this->_reallocate_data();
    this->_copy_data_from_another_range(list);

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixEqualityOperationRequires<U>
bool Matrix<T>::operator == (const Matrix<U>& matrix) const
{
    return std::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<MatrixType T>
template <typename U> requires MatrixEqualityOperationRequires<U>
    bool Matrix<T>::equality(const Matrix<U>& matrix) const
{
    return std::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<MatrixType T>
template <typename U> requires MatrixEqualityOperationRequires<U>
bool Matrix<T>::operator != (const Matrix<U>& matrix) const
{
    return !std::ranges::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<MatrixType T>
Matrix<T>::MatrixRow Matrix<T>::operator [] (const size_t row)
{
    if (this->_rows <= row)
        throw ExceptionOutOfIndex(__FILE__,  __LINE__, "Icorrect row index.");

    return MatrixRow(*this, row);
}

template<MatrixType T>
Matrix<T>::MatrixRow Matrix<T>::operator [] (const size_t row) const
{
    if (this->_rows <= row)
        throw ExceptionOutOfIndex(__FILE__, __LINE__, "Icorrect row index.");

    return MatrixRow(*this, row);
}

template<MatrixType T>
T &Matrix<T>::operator()(size_t row, size_t column)
{
    return this->_data[row * this->_columns + column];
}

template<MatrixType T>
const T &Matrix<T>::operator()(size_t row, size_t column) const
{
    return this->_data[row * this->_columns + column];
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T> &Matrix<T>::sum_matrix(const Matrix<U>& matrix)
{
    (*this) += matrix;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T> Matrix<T>::sum_matrix(const Matrix<U>& matrix) const
{
    Matrix<T> buffer(*this);

    buffer += matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T> &Matrix<T>::sum_value(const U& value)
{
    (*this) += value;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
    Matrix<T> Matrix<T>::sum_value(const U& value) const
{
    Matrix<T> buffer(*this);

    buffer += value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T> &Matrix<T>::sub_value(const U& value)
{
    (*this) -= value;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T> Matrix<T>::sub_value(const U& value) const
{
    Matrix<T> buffer(*this);

    buffer -= value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T> &Matrix<T>::sub_matrix(const Matrix<U>& matrix)
{
    (*this) -= matrix;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T> Matrix<T>::sub_matrix(const Matrix<U>& matrix) const
{
    Matrix<T> buffer(*this);

    buffer -= matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T> &Matrix<T>::mul_matrix(const Matrix<U>& matrix)
{
    (*this) *= matrix;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T> Matrix<T>::mul_matrix(const Matrix<U>& matrix) const
{
    Matrix<T> buffer(*this);

    buffer *= matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T> &Matrix<T>::div_value(const U &value)
{
    (*this) /= value;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T> Matrix<T>::div_value(const U &value) const
{
    Matrix<T> buffer(*this);

    buffer /= value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T> &Matrix<T>::div_matrix(const Matrix<U>& matrix)
{
    (*this) /= matrix;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T> Matrix<T>::div_matrix(const Matrix<U>& matrix) const
{
    Matrix<T> buffer(*this);

    buffer /= matrix;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T> &Matrix<T>::mul_value(const U &value)
{
    (*this) *= value;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T> Matrix<T>::mul_value(const U &value) const
{
    Matrix<T> buffer(*this);

    buffer *= value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator += (const Matrix<U>& matrix)
{
    this->_validate_another_matrix_params(matrix._rows, matrix._columns, __LINE__);

    std::transform(this->begin(), this->end(), matrix.begin(), this->begin(),
                   [](auto &left, auto &right) { return left + right; });

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator += (const U& value)
{
    std::transform(this->begin(), this->end(), this->begin(),
                   [value] (auto &left) { return left + value; });

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator -= (const Matrix<U>& matrix)
{
    this->_validate_another_matrix_params(matrix._rows, matrix._columns, __LINE__);

    std::transform(this->begin(), this->end(), matrix.begin(), this->begin(),
                   [](auto &left, auto &right) { return left - right; });

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator -= (const U& value)
{
    std::transform(this->begin(), this->end(), this->begin(),
                   [value](auto &left) { return left - value; });

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator *= (const Matrix<U>& matrix)
{
    if (this->_columns != matrix._rows)
        throw ExceptionImpossibleOperation(__FILE__,  __LINE__, "Incorrect count of rows vs columns for mul.");

    Matrix<T> buffer(this->_rows, matrix._columns);

    for (size_t i = 0; i < buffer._columns; i++)
    {
        Matrix<T> buffer_column(1, matrix._rows);

        for (size_t j = 0; j < matrix._rows; j++)
            buffer_column[0][j] = matrix[j][i];

        for (size_t j = 0; j < buffer._rows; j++)
            buffer[j][i] = std::inner_product(buffer_column.begin(), buffer_column.end(), this->begin() + j * this->_columns, 0);
    }

    *this = buffer;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator *= (const U &value)
{
    this->_validate_empty(__LINE__);

    std::transform(this->begin(), this->end(), this->begin(),
                   [value](auto &left, auto &right) { return left * value; });

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T>& Matrix<T>::operator /= (const U &value)
{
    if (value == 0)
        ExceptionImpossibleToDivide(__FILE__, __LINE__);

    this->_validate_empty(__LINE__);

    for (auto &x: *this) x /= value;

    return *this;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
    Matrix<T>& Matrix<T>::operator /= (const Matrix<U> &matrix)
{
    if (this->_columns != matrix._rows)
        throw ExceptionImpossibleOperation(__FILE__,  __LINE__, "Incorrect count of rows vs columns for div.");

    Matrix<T> buffer = matrix.inverse();

    return this->mul(buffer);
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T> Matrix<T>::operator + (const Matrix<U>& matrix) const
{
    Matrix<T> buffer (*this);

    buffer += matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSumOperationRequires<T, U>
Matrix<T> Matrix<T>::operator + (const U& value) const
{
    Matrix<T> buffer (*this);

    buffer += value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
Matrix<T> Matrix<T>::operator - (const Matrix<U>& matrix) const
{
    Matrix<T> buffer (*this);

    buffer -= matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixSubOperationRequires<T, U>
    Matrix<T> Matrix<T>::operator - (const U& value) const
{
    Matrix<T> buffer (*this);

    buffer -= value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
Matrix<T> Matrix<T>::operator * (const Matrix<U>& matrix) const
{
    Matrix<T> buffer (*this);

    buffer *= matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixMulOperationRequires<T, U>
    Matrix<T> Matrix<T>::operator * (const U &value) const
{
    Matrix<T> buffer (*this);

    buffer *= value;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T> Matrix<T>::operator / (const Matrix<U>& matrix) const
{
    Matrix<T> buffer(this);

    buffer /= matrix;

    return buffer;
}

template<MatrixType T>
template <typename U> requires MatrixDivOperationRequires<T, U>
Matrix<T> Matrix<T>::operator / (const U &value) const
{
    Matrix<T> buffer(this);

    buffer /= value;

    return buffer;
}

template<MatrixType T>
size_t Matrix<T>::get_rows_count() const
{
    return this->_rows;
}

template<MatrixType T>
Matrix<T>::iterator Matrix<T>::begin()
{
    return Iterator<T>(*this, 0);
}

template<MatrixType T>
Matrix<T>::iterator Matrix<T>::end()
{
    return Iterator<T>(*this, this->_rows * this->_columns);
}

template<MatrixType T>
Matrix<T>::const_iterator Matrix<T>::begin() const
{
    return IteratorConst<T>(*this, 0);
}

template<MatrixType T>
Matrix<T>::const_iterator  Matrix<T>::end() const
{
    return IteratorConst<T>(*this, this->_rows * this->_columns);
}

template<MatrixType T>
Matrix<T>::const_iterator  Matrix<T>::cbegin() const
{
    return IteratorConst<T>(*this, 0);
}

template<MatrixType T>
Matrix<T>::const_iterator Matrix<T>::cend() const
{
    return IteratorConst<T>(*this, this->_rows * this->_columns);
}

template<MatrixType T>
Matrix<T>::reverse_iterator Matrix<T>::rend()
{
    return std::reverse_iterator(Iterator<T>(*this, -1));
}

template<MatrixType T>
Matrix<T>::reverse_iterator Matrix<T>::rbegin()
{
    return std::reverse_iterator(Iterator(*this, this->size() - 1) );
}

template<MatrixType T>
Matrix<T>::const_reverse_iterator Matrix<T>::rend() const
{
    return std::reverse_iterator(Iterator<T>(*this, -1));
}

template<MatrixType T>
Matrix<T>::const_reverse_iterator  Matrix<T>::rbegin() const
{
    return std::reverse_iterator(Iterator(*this, this->size() - 1));
}

template<MatrixType T>
Matrix<T>::const_reverse_iterator Matrix<T>::rcend() const
{
    return std::reverse_iterator(IteratorConst<T>(*this, -1));
}

template<MatrixType T>
Matrix<T>::const_reverse_iterator Matrix<T>::rcbegin() const
{
    return std::reverse_iterator(IteratorConst<T>(*this, this->_size() - 1));
}

template<MatrixType T>
size_t Matrix<T>::size() const
{
    return this->_rows * this->_columns;
}

template<MatrixType T>
Matrix<T> &Matrix<T>::_reallocate_data()
{
    try
    {
        this->_data.reset(new T[this->_rows * this->_columns]);
    }
    catch (std::bad_alloc)
    {
        throw ExceptionBadAllocate(__FILE__, __LINE__);
    }

    return *this;
}

template<MatrixType T>
Matrix<T> &Matrix<T>::_copy_data_from_another_range(auto &range)
{
    auto iter_1 = this->begin();

    for (auto &iter: range)
        if (this->_columns != iter.size())
        {
            throw ExceptionOutOfIndex(__FILE__, __LINE__, "Error of list element.");
        }
        else
        {
            std::ranges::copy(iter, iter_1);
            iter_1 += this->_columns;
        }

    return *this;
}

template<MatrixType T>
Matrix<T> &Matrix<T>::_check_possibility_to_inverse()
{
    if (!this->is_square())
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "Inversion is not availiable.");

    Matrix<T> buffer_1 = (*this) * this->transpose();

    if (buffer_1.is_unit())
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "Inversion is not availiable.");

    if (this->get_det() == 0)
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "Inversion is not availiable.");

    return *this;
}
