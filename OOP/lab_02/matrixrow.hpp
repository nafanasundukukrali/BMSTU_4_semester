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
void MatrixRow<T>::reset_data(T* data, size_t new_size)
{
    this->_size = new_size;
    this->_data.reset(data);
}
