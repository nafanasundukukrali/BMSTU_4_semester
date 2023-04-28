#include <ranges>
#include <concepts>
#include "matrix.h"
#include "exceptionmatrix.h"

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns): MatrixBase(rows, columns)
{
    if (rows == 0 || columns == 0)
        ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Matrix params incorrect. ");

    this->_reallocate_data();
}

template<typename T>
Matrix<T>::Matrix(const Matrix &matrix): MatrixBase(matrix._rows, matrix._columns)
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

    for (auto &iter: list)
        if (this->_columns != iter.size())
        {
            ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Error of list element.");
        }
        else
        {
            std::ranges::copy(iter, this->_data[i].begin());
            i++;
        }
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
{
    _rows = matrix._rows;
    _columns = matrix._colums;

    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        std::ranges::copy(matrix._data[i].begin(), matrix._data[i].end(), this->_data[i].begin());

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& matrix)
{
    _rows = matrix._rows;
    _columns = matrix._colums;
    this->_data = matrix._data;

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (std::initializer_list<std::initializer_list<T>> list)
{
    this->_rows = list.size();
    this->_rows = list.begin->size();

    this->_reallocate_data();

    size_t i = 0;

    for (auto &iter: list)
        if (this->_columns != iter.size())
        {
            ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Error of list element.");
        }
        else
        {
            std::ranges::copy(iter, this->_data[i].begin());
            i++;
        }
}

template <typename T>
Iterator<Matrix, MatrixRow<T>> Matrix<T>::begin()
{
    return Iterator<Matrix, MatrixRow<T>>(*this, 0);
}

template <typename T>
Iterator<Matrix, MatrixRow<T>> Matrix<T>::end()
{
    return Iterator<Matrix, MatrixRow<T>>(*this, this->_collums * this->_rows);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>> Matrix<T>::begin() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, 0);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>>  Matrix<T>::end() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, this->_columns * this->_rows);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>>  Matrix<T>::cbegin() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, 0);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>> Matrix<T>::cend() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, this->_columns * this->_rows);
}


template <typename T>
Iterator<Matrix, MatrixRow<T>> Matrix<T>::rbegin()
{
    return Iterator<Matrix, MatrixRow<T>>(*this, this->_collums * this->_rows - 1);
}

template <typename T>
Iterator<Matrix, MatrixRow<T>> Matrix<T>::rend()
{
    return Iterator<Matrix, MatrixRow<T>>(*this, -1);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>> Matrix<T>::rbegin() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, this->_collums * this->_rows - 1);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>> Matrix<T>::rend() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, -1);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>> Matrix<T>::crbegin() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, this->_collums * this->_rows - 1);
}

template <typename T>
IteratorConst< Matrix, MatrixRow<T>> Matrix<T>::crend() const
{
    return IteratorConst< Matrix, MatrixRow<T>>(*this, -1);
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
