#include "iterator.h"
#include "exceptionmatrix.h"

template<MatrixType T>
Iterator<T>::Iterator(const Matrix<T> &container, const size_t index)
{
    this->_index = index;
    this->_data = container._data;
    this->_size = container.size();
}

template<MatrixType T>
Iterator<T>::Iterator(Matrix<T> &container, const size_t index)
{
    this->_index = index;
    this->_data = container._data;
    this->_size = container.size();
}

template<MatrixType T>
bool Iterator<T>::operator != (Iterator<T> const& iterator) const
{
    return this->_index != iterator._index;
}

template<MatrixType T>
bool Iterator<T>::operator == (Iterator<T> const& other) const
{
    return this->_index == other._index;
}

template<MatrixType T>
bool Iterator<T>::operator < (Iterator<T> const& other) const
{
    return this->_index < other._index;
}

template<MatrixType T>
bool Iterator<T>::operator > (Iterator<T> const& other) const
{
    return this->_index > other._index;
}

template<MatrixType T>
bool Iterator<T>::operator >= (Iterator<T> const& other) const
{
    return this->_index >= other._index;
}

template<MatrixType T>
bool Iterator<T>::operator <= (Iterator<T> const& other) const
{
    return this->_index >= other._index;
}

template<MatrixType T>
Iterator<T>::iterator Iterator<T>::operator + (const size_t value) const
{
    iterator buffer(*this);

    buffer._increase(value);

    return buffer;
}

template<MatrixType T>
Iterator<T>::iterator Iterator<T>::operator - (const size_t value) const
{
    iterator buffer(*this);

    buffer._dicrease(value);

    return buffer;
}

template<MatrixType T>
Iterator<T>::iterator &Iterator<T>::operator += (const size_t value)
{
    this->_increase(value);

    return *this;
}


template<MatrixType T>
Iterator<T>::iterator &Iterator<T>::operator -= (const size_t value)
{
    this->_dicrease(value);

    return *this;
}

template<MatrixType T>
Iterator<T>::iterator &Iterator<T>::operator = (const Iterator<T>::iterator &iterator)
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_columns = iterator._columns;

    return *this;
}

template<MatrixType T>
Iterator<T>::iterator &Iterator<T>::operator = (Iterator<T>::iterator &&iterator) noexcept
{
    this->_index = iterator._index;
    this->_data = iterator._data;
    this->_size = iterator._size;

    return *this;
}

template<MatrixType T>
Iterator<T>::iterator &Iterator<T>::operator ++()
{
    this->_increase(1);

    return *this;
}

template<MatrixType T>
Iterator<T>::iterator Iterator<T>::operator ++(int)
{
    Iterator<T> buffer(*this);
    this->_increase(1);

    return buffer;
}


template<MatrixType T>
Iterator<T>::iterator &Iterator<T>::operator --()
{
    this->_dicrease(1);

    return *this;
}

template<MatrixType T>
Iterator<T> Iterator<T>::operator --(int)
{
    Iterator<T> buffer(*this);
    this->_dicrease(1);

    return buffer;
}

template<MatrixType T>
Iterator<T>::difference_type Iterator<T>::operator - (const iterator &it)
{
    return std::max(this->_index, it._index) - std::min(this->_index, it._index);
}


template<MatrixType T>
T &Iterator<T>::operator *()
{
    this->_check_data_expairing(__LINE__);

    if (this->_index >= this->_size)
        ExceptionIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<MatrixType T>
T &Iterator<T>::operator *() const
{
    this->_check_data_expairing(__LINE__);

    if (this->_index >= this->_size)
        ExceptionIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<MatrixType T>
T *Iterator<T>::operator ->()
{
    this->_check_data_expairing(__LINE__);

    if (this->_index >= this->_size)
        ExceptionIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<MatrixType T>
T *Iterator<T>::operator ->() const
{
    this->_check_data_expairing(__LINE__);

    if (this->_index >= this->_size)
        ExceptionIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<MatrixType T>
T &Iterator<T>::operator[](const size_t index)
{
    this->_check_data_expairing(__LINE__);

    size_t new_index = this->_index + index;

    if (new_index >= this->size)
        ExceptionIndex(__FILE__, __LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + index);
}

template<MatrixType T>
T &Iterator<T>::operator[](const size_t index) const
{
    this->_check_data_expairing(__LINE__);

    size_t new_index = this->_index + index;

    if (new_index >= this->size)
        ExceptionIndex(__FILE__, __LINE__);

    return *(this->_data.get() + index);
}

template<MatrixType T>
void Iterator<T>::_check_valid_index(size_t line) const
{
    if (this->_index < this->_size)
        return;

    throw ExceptionIndex(__FILE__, line);
}

template<MatrixType T>
void Iterator<T>::_check_data_expairing(size_t line) const
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, line);
}

template<MatrixType T>
void Iterator<T>::_increase(size_t count)
{
    this->_check_data_expairing(__LINE__);
    this->_check_valid_index(__LINE__);

    size_t new_index = this->_index + count;

    if (new_index > this->_size)
        throw ExceptionIndex(__FILE__, __LINE__);

    this->_index += count;
}

template<MatrixType T>
void Iterator<T>::_dicrease(size_t count)
{
    this->_check_data_expairing(__LINE__);
    this->_check_valid_index(__LINE__);

    size_t new_index = this->_index - count;

    if (new_index >= this->_size && new_index != size_t(0) - 1)
        throw ExceptionIndex(__FILE__, __LINE__);

    this->_index -= count;
}
