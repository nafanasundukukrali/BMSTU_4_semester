#include "matrixrow.h"
#include "concepts.h"
#include <ranges>

template<typename T>
MatrixRow<T>::MatrixRow(std::initializer_list<T> list): MatrixBase(1, list.size())
{
    this->_reallocate_data();

    std::ranges::copy(list, this->begin());
}

template<typename T>
MatrixRow<T>::MatrixRow(const MatrixRow<T> &row):  MatrixBase(1, row._columns)
{
    this->_reallocate_data();

    std::copy(row.begin(), row.end(), this->begin());
}

template<typename T>
MatrixRow<T>::MatrixRow(MatrixRow<T> &&row): MatrixBase(1, row._columns)
{
    this->_data = row._data;
}

template<typename T>
T& MatrixRow<T>::operator[](size_t column)
{
    if (this->_columns <= column)
       ExceptionIndex(__FILE__, this->get_class_name(), __LINE__, "Column number is out of range.");

    return this->_data[column];
}

template<typename T>
const T& MatrixRow<T>::operator[](size_t column) const
{
    if (this->_columns <= column)
       ExceptionIndex(__FILE__, this->get_class_name(), __LINE__, "Column number is out of range.");

    return this->_data[column];
}

template<typename T>
MatrixRow<T>& MatrixRow<T>::operator = (MatrixRow<T>&& row)
{
    this->_rows = row._rows;
    this->_columns = row._columns;
    this->_data = row._data;

    return *this;
}

template<typename T>
MatrixRow<T>& MatrixRow<T>::operator = (const MatrixRow<T>& row)
{
    this->_rows = row._rows;
    this->_columns = row._columns;

    this->_reallocate_data();

    std::copy(row.begin(), row.end(), this->begin());

    return *this;
}

template<typename T>
void MatrixRow<T>::reset_data(T *data, size_t new_size)
{
    this->_columns = new_size;
    this->_data.reset(data);
}

template<typename T>
bool MatrixRow<T>::operator == (const MatrixRow<T>& row) const
{
    return std::equal(this->begin(), this->end(), row.begin(), row.end());
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    MatrixRow<T> MatrixRow<T>::operator + (const MatrixRow<U>& row)
{
    row._validate_empty_new();
    this->validate_empty();
    this->validate_another_matrix_row_params(row._rows, row._columns);

    MatrixRow<T> buffer(*this);

    std::transform(buffer.begin(), buffer.end(), row.begin(), buffer.begin(),
                   [](T left, T right) { return left + right; });

    return buffer;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    MatrixRow<T> MatrixRow<T>::operator - (const MatrixRow<U>& row)
{
    row._validate_empty_new();
    this->validate_empty();
    this->validate_another_matrix_row_params(row._rows, row._columns);

    MatrixRow<T> buffer(*this);

    std::transform(buffer.begin(), buffer.end(), row.begin(), buffer.begin(),
                   [](T left, T right) { return left - right; });

    return buffer;
}

template<typename T>
MatrixRow<T> MatrixRow<T>::operator * (const T value)
{
    MatrixRow<T> buffer(*this);

    std::for_each(buffer.begin(), buffer.end(), [v = value](T& el) mutable { el *= v; });

    return buffer;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
MatrixRow<T>& MatrixRow<T>::operator += (const MatrixRow<U>& row)
{
    *this = (*this) + row;

    return *this;
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
    MatrixRow<T>& MatrixRow<T>::operator -= (const MatrixRow<U>& row)
{
    *this = (*this) - row;

    return *this;
}

template<typename T>
MatrixRow<T>& MatrixRow<T>::operator *= (const T value)
{
    *this = (*this) * value;

    return *this;
}

template<typename T>
void MatrixRow<T>::add_column(size_t post_position, T value)
{
    if (post_position > this->_columns)
       ExceptionIndex(__FILE__, this->get_class_name(), __LINE__);

    std::shared_ptr<T[]> buffer = nullptr;
    buffer.reset(new T[this->_columns + 1]);

    size_t i = 0;

    while (i < post_position) {
       buffer[i] = this->_data[i];
       i++;
    }

    buffer[i] = value;
    i++;

    while (i < this->_columns + 1)
    {
       buffer[i] = this->_data[i - 1];
       i++;
    }

    this->_data = buffer;
    this->_columns += 1;
}

template<typename T>
void MatrixRow<T>::delete_column(size_t column_number)
{
    if (column_number >= this->_columns)
       ExceptionIndex(__FILE__, this->get_class_name(), __LINE__);

    std::shared_ptr<T[]> buffer = nullptr;
    buffer.reset(new T[this->_columns - 1]);

    size_t i = 0;

    while (i < column_number) {
       buffer[i] = this->_data[i];
       i++;
    }
    i++;

    while (i < this->_columns)
    {
       buffer[i - 1] = this->_data[i];
       i++;
    }

    this->_data = buffer;
    this->_columns -= 1;
}

template <typename T>
void MatrixRow<T>::_reallocate_data()
{
    try
    {
       this->_data.reset(new T[this->_columns]);
    }
    catch (std::bad_alloc)
    {
       throw ExceptionBadAllocate(__FILE__, this->get_class_name(), __LINE__);
    }
}

template <typename T>
Iterator<MatrixRow, T> MatrixRow<T>::begin()
{
    return Iterator<MatrixRow, T>(*this, 0);
}

template <typename T>
Iterator<MatrixRow, T> MatrixRow<T>::end()
{
    return Iterator<MatrixRow, T>(*this, this->_columns);
}

template <typename T>
IteratorConst<MatrixRow, T> MatrixRow<T>::begin() const
{
    return IteratorConst<MatrixRow, T>(*this, 0);
}

template <typename T>
IteratorConst<MatrixRow, T> MatrixRow<T>::end() const
{
    return IteratorConst<MatrixRow, T>(*this, this->_columns);
}

template <typename T>
IteratorConst<MatrixRow, T> MatrixRow<T>::cbegin() const
{
    return IteratorConst<MatrixRow, T>(*this, 0);
}

template <typename T>
IteratorConst<MatrixRow, T> MatrixRow<T>::cend() const
{
    return IteratorConst<MatrixRow, T>(*this, this->_columns);
}

template <typename T>
size_t MatrixRow<T>::size() const
{
    return this->_rows *this->_columns;
}
