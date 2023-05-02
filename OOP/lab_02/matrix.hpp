#include <ranges>
#include <concepts>
#include <numeric>
#include "matrix.h"
#include "exceptionmatrix.h"

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns): MatrixBase(rows, columns)
{
    if (rows == 0 || columns == 0)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Matrix params incorrect. ");

    this->_reallocate_data();
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &matrix): MatrixBase(matrix._rows, matrix._columns)
{
    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        std::ranges::copy(matrix._data[i].begin(), matrix._data[i].end(), this->_data[i].begin());
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &&matrix): MatrixBase(matrix._rows, matrix._columns)
{
    this->_data = matrix._data;
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list): MatrixBase(list.size(), list.begin()->size())
{
    this->_reallocate_data();

    size_t i = 0;

    this->_copy_data_from_another_range(list);
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;

    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        std::ranges::copy(matrix._data[i].begin(), matrix._data[i].end(), this->_data[i].begin());

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;
    this->_data = matrix._data;

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (std::initializer_list<std::initializer_list<T>> list)
{
    this->_rows = list.size();
    this->_rows = list.begin->size();

    this->_reallocate_data();

    this->_copy_data_from_another_range(list);
}

template<typename T>
bool Matrix<T>::operator == (const Matrix<T>& matrix) const
{
    return std::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<typename T>
bool Matrix<T>::operator != (const Matrix<T>& matrix) const
{
    return !std::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<typename T>
MatrixRow<T>& Matrix<T>::operator [] (size_t row)
{
    if (this->_rows <= row)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Icorrect row index.");

    return this->_data[row];
}

template<typename T>
const MatrixRow<T>& Matrix<T>::operator [] (size_t row) const
{
    if (this->_rows <= row)
        throw ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Icorrect row index.");

    return this->_data[row];
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
Matrix<T> Matrix<T>::sum(const Matrix<U>& matrix)
{
    this->validate_another_matrix_row_params(matrix._rows, matrix._columns);

    Matrix<T> buffer(*this);

    std::transform(buffer.begin(), buffer.end(), matrix.begin(), buffer.begin(),
                   [](MatrixRow<T> left, MatrixRow<T> right) { return left + right; });

    return buffer;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T> Matrix<T>::sub(const Matrix<U>& matrix)
{
    this->validate_another_matrix_row_params(matrix._rows, matrix._columns);

    Matrix<T> buffer(*this);

    std::transform(buffer.begin(), buffer.end(), matrix.begin(), buffer.begin(),
                   [](MatrixRow<T> left, MatrixRow<T> right) { return left - right; });

    return buffer;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T> Matrix<T>::mul(const Matrix<U>& matrix)
{
    if (this->_columns != matrix._rows)
        throw ExceptionImpossibleOperation(__FILE__, this->_get_class_name(), __LINE__, "Incorrect count of rows vs columns for mul.");

    Matrix<T> buffer(this->_rows, matrix._columns);


    for (size_t i = 0; i < buffer._columns; i++)
    {
        MatrixRow<T> buffer_column;

        buffer_column.reset_data(new T[matrix._rows], matrix._rows);

        std::transform(matrix.begin(), matrix.end(), buffer_column.begin(),
                       [matrix, i] (auto &row_1) {return row_1[i];});

        for (size_t j = 0; j < buffer._rows; j++)
            buffer[j][i] = std::inner_product(buffer_column.begin(), buffer_column.end(), (*this)[j].begin(), 0);
    }

    return buffer;
}

template<typename T>
Matrix<T> Matrix<T>::mul(const T value)
{
    Matrix<T> buffer(*this);

    for (auto &row: buffer) row *= value;

    return buffer;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
Matrix<T>& Matrix<T>::operator += (const Matrix<U>& matrix)
{
    *this = this->sum(matrix);

    return *this;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T>& Matrix<T>::operator -= (const Matrix<U>& matrix)
{
    *this = this->sub(matrix);

    return *this;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T>& Matrix<T>::operator *= (const Matrix<U>& matrix)
{
    *this = this->mul(matrix);
    this->_columns = matrix._columns;

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator *= (const T value)
{
    *this = this->mul(value);

    return *this;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T> Matrix<T>::operator + (const Matrix<U>& matrix)
{
    return this->sum(matrix);
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T> Matrix<T>::operator - (const Matrix<U>& matrix)
{
    return this->sub(matrix);
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    Matrix<T> Matrix<T>::operator * (const Matrix<U>& matrix)
{
    return this->mul(matrix);
    this->_columns = matrix._columns;
}

template<typename T>
void Matrix<T>::change_columns(size_t from_position, size_t to_position)
{
    if (this->_columns <= from_position || this->_columns <= to_position)
        throw ExceptionIndex(__FILE__, this->_->_get_class_name(), __LINE__, "Inccorect input positions.");

    std::transform(this->begin(), this->end(), this->begin(), [=] (auto &row){
        std::swap(row[from_position], row[to_position]);
        return row;
    });
}

template<typename T>
void Matrix<T>::change_rows(size_t from_position, size_t to_position)
{
    if (this->_rows <= from_position || this->_rows <= to_position)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Inccorect input positions.");

    std::swap_ranges(this->_data[from_position].begin(),
                     this->_data[from_position].end(),
                     this->_data[to_position].begin());
}

template<typename T>
void Matrix<T>::add_column(size_t post_column_number, std::initializer_list<T> list)
{
    if (this->_columns < post_column_number || list.size() != this->_rows)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Inccorect input positions.");

    size_t list_i = 0;

    for (auto &row: *this)
    {
        row.add_column(post_column_number, *(list.begin() + list_i));
        list_i++;
    }

    this->_columns++;
}

template<typename T>
void Matrix<T>::add_row(size_t post_column_number, std::initializer_list<T> list)
{
    if (list.size() != this->_columns || this->_rows < post_column_number)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Inccorect input positions.");

    std::shared_ptr<MatrixRow<T>[]> buffer = nullptr;
    buffer.reset(new MatrixRow<T>[this->_rows + 1]);

    size_t i = 0;

    while (i < post_column_number) {
        buffer[i] = this->_data[i];
        i++;
    }

    MatrixRow<T> buffer_1(list);

    buffer[i] = buffer_1;

    i++;

    while (i < this->_rows + 1)
    {
        buffer[i] = this->_data[i - 1];
        i++;
    }

    this->_data = buffer;
    this->_rows++;
}

template<typename T>
void Matrix<T>::delete_column(size_t delete_column_number)
{
    if (this->_columns <= delete_column_number)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Inccorect input positions.");

    for (auto &row: *this)
        row.delete_column(delete_column_number);

    this->_columns--;
}

template<typename T>
void Matrix<T>::delete_row(size_t delete_column_number)
{
    if (this->_rows <= delete_column_number)
        throw ExceptionIndex(__FILE__, this->_get_class_name(), __LINE__, "Inccorect input positions.");

    std::shared_ptr<MatrixRow<T>[]> buffer = nullptr;
    buffer.reset(new MatrixRow<T>[this->_rows - 1]);

    size_t i = 0;

    while (i < delete_column_number) {
        buffer[i] = this->_data[i];
        i++;
    }

    i++;

    while (i < this->_rows)
    {
        buffer[i - 1] = this->_data[i];
        i++;
    }

    this->_data = buffer;
    this->_rows--;
}

template<typename T>
size_t Matrix<T>::get_rows_count() const
{
    return this->_rows;
}

template<typename T>
Matrix<T> Matrix<T>::operator * (const T value)
{
    return this->mul(value);
}

template <typename T>
Iterator<Matrix, T, MatrixRow<T>> Matrix<T>::begin()
{
    return Iterator<Matrix, T, MatrixRow<T>>(*this, size_t(0));
}

template <typename T>
Iterator<Matrix, T, MatrixRow<T>> Matrix<T>::end()
{
    return Iterator<Matrix, T, MatrixRow<T>>(*this, this->_rows);
}

template <typename T>
IteratorConst<Matrix, T, MatrixRow<T>> Matrix<T>::begin() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, 0);
}

template <typename T>
IteratorConst<Matrix, T, MatrixRow<T>>  Matrix<T>::end() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, this->_rows);
}

template <typename T>
IteratorConst<Matrix, T, MatrixRow<T>>  Matrix<T>::cbegin() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, 0);
}

template <typename T>
IteratorConst<Matrix, T, MatrixRow<T>> Matrix<T>::cend() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, this->_rows);
}

template <typename T>
void Matrix<T>::_reallocate_data()
{
    try
    {
        this->_data.reset(new MatrixRow<T>[this->_rows]);

        for (size_t i = 0; i < this->_rows; i++)
            this->_data[i].reset_data(new T[this->_columns], this->_columns);
    }
    catch (std::bad_alloc)
    {
        throw ExceptionBadAllocate(__FILE__, typeid(*this).name(), __LINE__);
    }
}

template <typename T>
void Matrix<T>::_copy_data_from_another_range(auto &range)
{
    size_t i = 0;

    for (auto &iter: range)
        if (this->_columns != iter.size())
        {
            throw ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Error of list element.");
        }
        else
        {
            std::ranges::copy(iter, this->_data[i].begin());
            i++;
        }
}
