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
Matrix<T>::Matrix(const Matrix&Matrix): MatrixBase(Matrix._rows, Matrix._columns)
{
    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        for (size_t j = 0; j < this->_columns; j++)
            this->_data[i][j] = Matrix._data[i][j];
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&&Matrix): MatrixBase(Matrix._rows, Matrix._columns)
{
    this->_data = Matrix._data;
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list): MatrixBase(list.size(), list.begin()->size())
{
    this->_reallocate_data();

    size_t i = 0;

    for (auto &iter: list)
        if (this->_columns != iter.size())
            ExceptionIndex(__FILE__, typeid(*this).name(), __LINE__, "Error of list element.");
        else
            std::ranges::copy(iter, this->_data[i].begin());
}


template <typename T>
Iterator<T> Matrix<T>::begin()
{
    return Iterator<T>(*this, 0);
}

template <typename T>
Iterator<T> Matrix<T>::end()
{
    return Iterator<T>(*this, this->_collums * this->_rows);
}

template <typename T>
IteratorConst<T> Matrix<T>::begin() const
{
    return IteratorConst<T>(*this, 0);
}

template <typename T>
IteratorConst<T> Matrix<T>::end() const
{
    return IteratorConst<T>(*this, this->_columns * this->_rows);
}

template <typename T>
IteratorConst<T> Matrix<T>::cbegin() const
{
    return IteratorConst<T>(*this, 0);
}

template <typename T>
IteratorConst<T> Matrix<T>::cend() const
{
    return IteratorConst<T>(*this, this->_columns * this->_rows);
}


template <typename T>
Iterator<T> Matrix<T>::rbegin()
{
    return Iterator<T>(*this, this->_collums * this->_rows - 1);
}

template <typename T>
Iterator<T> Matrix<T>::rend()
{
    return Iterator<T>(*this, -1);
}

template <typename T>
IteratorConst<T> Matrix<T>::rbegin() const
{
    return IteratorConst<T>(*this, this->_collums * this->_rows - 1);
}

template <typename T>
IteratorConst<T> Matrix<T>::rend() const
{
    return IteratorConst<T>(*this, -1);
}

template <typename T>
IteratorConst<T> Matrix<T>::crbegin() const
{
    return IteratorConst<T>(*this, this->_collums * this->_rows - 1);
}

template <typename T>
IteratorConst<T> Matrix<T>::crend() const
{
    return IteratorConst<T>(*this, -1);
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
