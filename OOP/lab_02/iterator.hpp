#include "iterator.h"
#include "exceptionmatrix.h"

template <typename T>
bool Iterator<T>::operator != (Iterator const& iterator) const
{
    return this->_index != iterator._index;
}

template <typename T>
bool Iterator<T>::operator == (Iterator const& other) const
{
    return this->_index == other._index;
}

template <typename T>
bool Iterator<T>::operator < (Iterator const& other) const
{
    return this->_index < other._index;
}

template <typename T>
Iterator<T> Iterator<T>::operator + (const int value)
{
   if (value < 0 && this->_index < static_cast<size_t>(-value))
       this->_index = 0;
   else
       this->_index++;

   if (this->_index > this->_rows * this->_columns)
       this->_index = this->_rows * this->_columns;

   return this;
}

template <typename T>
Iterator<T> Iterator<T>::operator - (const int value)
{
    return operator + (-value);
}

template <typename T>
Iterator<T> &Iterator<T>::operator += (const int value)
{
    operator + (value);

    return *this;
}


template <typename T>
Iterator<T> &Iterator<T>::operator = (const Iterator<T> &iterator)
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_columns = iterator._columns;

    return *this;
}


template <typename T>
Iterator<T> &Iterator<T>::operator ++()
{
    if (this->_index < this->_columns *this->_rows)
        this->_index++;

    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator ++(int)
{
    Iterator& buffer = *this;
    ++(*this);

    return buffer;
}


template <typename T>
Iterator<T> &Iterator<T>::operator --()
{
    if (this->_index > 0)
        this->_index--;

    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator --(int)
{
    Iterator& buffer = *this;
    --(*this);

    return buffer;
}

template<typename T>
T &Iterator<T>::operator *()
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->check_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<typename T>
const T &Iterator<T>::operator *() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->check_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<typename T>
T *Iterator<T>::operator ->()
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->check_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<typename T>
const T *Iterator<T>::operator ->() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->check_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<typename T>
void Iterator<T>::_check_valid_index(size_t line, std::string class_name)
{
    if (this->index < this->_rows * this->_columns)
        return;

    throw ExceptionIndex(__FILE__, class_name, line);
}

template<typename T>
void Iterator<T>::_check_data_expairing(size_t line, std::string class_name)
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, class_name, line);
}
