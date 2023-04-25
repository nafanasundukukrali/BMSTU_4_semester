#include "matrixrow.h"

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


template <typename T>
Iterator<T, MatrixRow> MatrixRow<T>::begin()
{
    return Iterator<T, MatrixRow>(*this, 0);
}

template <typename T>
Iterator<T, MatrixRow> MatrixRow<T>::end()
{
    return Iterator<T, MatrixRow>(*this, this->_columns);
}

template <typename T>
IteratorConst<T, MatrixRow> MatrixRow<T>::begin() const
{
    return IteratorConst<T, MatrixRow>(*this, 0);
}

template <typename T>
IteratorConst<T, MatrixRow> MatrixRow<T>::end() const
{
    return IteratorConst<T, MatrixRow>(*this, this->_columns);
}

template <typename T>
IteratorConst<T, MatrixRow> MatrixRow<T>::cbegin() const
{
    return IteratorConst<T, MatrixRow>(*this, 0);
}

template <typename T>
IteratorConst<T, MatrixRow> MatrixRow<T>::cend() const
{
    return IteratorConst<T, MatrixRow>(*this, this->_columns);
}


//template <typename T>
//Iterator<T, MatrixRow> MatrixRow<T>::rbegin()
//{
//    return Iterator<T, MatrixRow>(*this, this->_collums - 1);
//}

//template <typename T>
//Iterator<T, MatrixRow> MatrixRow<T>::rend()
//{
//    return Iterator<T, MatrixRow>(*this, -1);
//}

//template <typename T>
//IteratorConst<T, MatrixRow> MatrixRow<T>::rbegin() const
//{
//    return IteratorConst<T, MatrixRow>(*this, this->_collums * this->_rows - 1);
//}

//template <typename T>
//IteratorConst<T, MatrixRow> MatrixRow<T>::rend() const
//{
//    return IteratorConst<MatrixRow<T>, Matrix>(*this, -1);
//}

//template <typename T>
//IteratorConst<T, MatrixRow> MatrixRow<T>::crbegin() const
//{
//    return IteratorConst<T, MatrixRow>(*this, this->_collums * this->_rows - 1);
//}

//template <typename T>
//IteratorConst<T, MatrixRow> MatrixRow<T>::crend() const
//{
//    return IteratorConst<T, MatrixRow>(*this, -1);
//}
