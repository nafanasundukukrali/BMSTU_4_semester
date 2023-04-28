#include "matrixrow.h"
#include "concepts.h"
#include <ranges>

template<typename T>
MatrixRow<T>::MatrixRow(std::initializer_list<std::initializer_list<T>> list): MatrixBase(1, list.size())
{
    this->_reallocate_data();

    std::ranges::copy(list, this->_data.begin());
}

template<typename T>
T& MatrixRow<T>::operator[](size_t column)
{
    if (this->_size <= column)
       ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Column number is out of range.");

    return this->_parent.data.get()[column];
}

template<typename T>
const T& MatrixRow<T>::operator[](size_t column) const
{
    if (this->_size <= column)
       ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Column number is out of range.");

    return this->_parent.data.get()[column];
}

template<typename T>
void MatrixRow<T>::reset_data(T *data, size_t new_size)
{
    this->_columns = new_size;
    this->_data.reset(data);
}

template<typename T>
template<typename U> requires FloatingType<U> && std::same_as<T, U>
MatrixRow<T> MatrixRow<T>::operator + (const MatrixRow<U>& row) const
{
    if (row.empty() || this->empty())
       ExceptionEmptyObject(__FILE__, typeid(this).name(), __LINE__);

    if (!validate_another_matrix_row_params(row._rows, row._columns))
       ExceptionIncorrectSrcParams(__FILE__, typeid(this).name(), __LINE__);

    std::for_each(row.begin(), row.end(), this->begin(), std::plus<T>());
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
