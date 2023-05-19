#include "const_iterator.h"
#include "exceptionmatrix.h"

template<MatrixType T>
IteratorConst<T>::IteratorConst(const Matrix<T> &container, const size_t index)
{
    this->_index = index;
    this->_data = container._data;
    this->_size = container._rows * container._columns;
}

template<MatrixType T>
IteratorConst<T>::IteratorConst(Matrix<T> &container, const size_t index)
{
    this->_index = index;
    this->_data = container._data;
    this->_size = container._rows * container._columns;
}

template<MatrixType T>
bool IteratorConst<T>::operator != (IteratorConst<T> const& IteratorConst) const
{
    return this->_index != IteratorConst._index;
}

template<MatrixType T>
bool IteratorConst<T>::operator == (IteratorConst<T> const& other) const
{
    return this->_index == other._index;
}

template<MatrixType T>
bool IteratorConst<T>::operator < (IteratorConst<T> const& other) const
{
    return this->_index < other._index;
}

template<MatrixType T>
bool IteratorConst<T>::operator > (IteratorConst<T> const& other) const
{
    return this->_index > other._index;
}

template<MatrixType T>
bool IteratorConst<T>::operator >= (IteratorConst<T> const& other) const
{
    return this->_index >= other._index;
}

template<MatrixType T>
bool IteratorConst<T>::operator <= (IteratorConst<T> const& other) const
{
    return this->_index >= other._index;
}

template<MatrixType T>
IteratorConst<T>::iterator IteratorConst<T>::operator + (const size_t value) const
{
    IteratorConst buffer(*this);

    this->_increase(value);

    return buffer;
}

template<MatrixType T>
IteratorConst<T>::iterator IteratorConst<T>::operator - (const size_t value) const
{
    IteratorConst buffer(*this);

    this->_dicrease(value);

    return buffer;
}

template<MatrixType T>
IteratorConst<T>::difference_type IteratorConst<T>::operator - (const iterator &it)
{
    return std::max(this->_index, it._index) - std::min(this->_index, it._index);
}

template<MatrixType T>
IteratorConst<T>::iterator &IteratorConst<T>::operator += (const size_t value)
{
    this->_increase(value);

    return *this;
}


template<MatrixType T>
IteratorConst<T>::iterator &IteratorConst<T>::operator -= (const size_t value)
{
    this->_dicrease(value);

    return *this;
}

template<MatrixType T>
IteratorConst<T>::iterator &IteratorConst<T>::operator ++()
{
    this->_increase(1);

    return *this;
}

template<MatrixType T>
IteratorConst<T>::iterator IteratorConst<T>::operator ++(int)
{
    IteratorConst<T> buffer(*this);
    this->_increase(1);

    return buffer;
}


template<MatrixType T>
IteratorConst<T>::iterator &IteratorConst<T>::operator --()
{
    this->_dicrease(1);

    return *this;
}

template<MatrixType T>
IteratorConst<T> IteratorConst<T>::operator --(int)
{
    IteratorConst<T> buffer(*this);
    this->_dicrease(1);

    return buffer;
}

template<MatrixType T>
T &IteratorConst<T>::operator *() const
{
    this->_check_data_expairing(__LINE__);

    if (this->_index >= this->_size)
        ExceptionOutOfIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<MatrixType T>
T *IteratorConst<T>::operator ->() const
{
    this->_check_data_expairing(__LINE__);

    if (this->_index >= this->_size)
        ExceptionOutOfIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<MatrixType T>
T &IteratorConst<T>::operator[](const size_t index) const
{
    this->_check_data_expairing(__LINE__);

    size_t new_index = this->_index + index;

    if (new_index >= this->_size)
        ExceptionOutOfIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + index);
}

template<MatrixType T>
void IteratorConst<T>::_check_valid_index(size_t line) const
{
    if (this->_index < this->_size)
        return;
    
    throw ExceptionOutOfIndex(__FILE__, line);
}

template<MatrixType T>
void IteratorConst<T>::_check_data_expairing(size_t line) const
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, line);
}

template<MatrixType T>
void IteratorConst<T>::_increase(size_t count)
{
    this->_check_data_expairing(__LINE__);
    this->_check_valid_index(__LINE__);

    size_t new_index = this->_index + count;

    if (new_index > this->_size)
        throw ExceptionOutOfIndex(__FILE__, __LINE__);

    this->_index += count;
}

template<MatrixType T>
void IteratorConst<T>::_dicrease(size_t count)
{
    this->_check_data_expairing(__LINE__);
    this->_check_valid_index(__LINE__);

    size_t new_index = this->_index - count;

    if (new_index >= this->size && new_index != size_t(0) - 1)
        throw ExceptionOutOfIndex(__FILE__, __LINE__);

    this->index_ -= count;
}

