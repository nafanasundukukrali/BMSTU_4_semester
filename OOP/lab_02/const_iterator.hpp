#include "const_iterator.h"
#include "exceptionmatrix.h"

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T>::IteratorConst(const Container<Class_T> &container, const size_t index)
{
    this->_index = index;
    this->_data = container._data;
    this->_rows = container._rows;
    this->_columns = container._columns;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
bool IteratorConst<Container, Class_T, T>::operator != (IteratorConst<Container, Class_T, T> const& iterator) const
{
    return this->_index != iterator._index;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
bool IteratorConst<Container, Class_T, T>::operator == (IteratorConst<Container, Class_T, T> const& other) const
{
    return this->_index == other._index;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
bool IteratorConst<Container, Class_T, T>::operator < (IteratorConst<Container, Class_T, T> const& other) const
{
    return this->_index < other._index;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator + (const size_t value)
{
    IteratorConst<Container, Class_T, T> buffer(*this);

    buffer += value;

    return buffer;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator - (const size_t value)
{
    IteratorConst<Container, Class_T, T> buffer(*this);

    buffer -= value;

    return buffer;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> &IteratorConst<Container, Class_T, T>::operator += (const size_t value)
{
    this->_check_data_expairing(__LINE__);

    this->_index += value;

    this->_check_valid_index(__LINE__);

    return *this;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
    IteratorConst<Container, Class_T, T> &IteratorConst<Container, Class_T, T>::operator -= (const size_t value)
{
    this->_check_data_expairing(__LINE__);

    this->_index -= value;

    this->_check_valid_index(__LINE__);

    return *this;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> &IteratorConst<Container, Class_T, T>::operator = (const IteratorConst<Container, Class_T, T> &iterator)
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_columns = iterator._columns;

    return *this;
}


template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> &IteratorConst<Container, Class_T, T>::operator ++()
{
    if (this->_index < this->_columns *this->_rows)
       this->_index++;

    return *this;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator ++(int)
{
    IteratorConst<Container, Class_T, T> buffer(*this);

    ++(*this);

    return buffer;
}


template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> &IteratorConst<Container, Class_T, T>::operator --()
{
    if (this->_index > 0)
       this->_index--;

    return *this;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator --(int)
{
    IteratorConst<Container, Class_T, T> buffer(*this);

    --(*this);

    return buffer;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
T &IteratorConst<Container, Class_T, T>::operator *() const
{
    this->_check_data_expairing(__LINE__);
    this->_check_valid_index(__LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
T *IteratorConst<Container, Class_T, T>::operator ->() const
{
    this->_check_data_expairing(__LINE__);
    this->_check_valid_index(__LINE__);

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
void IteratorConst<Container, Class_T, T>::_check_valid_index(const size_t line) const
{
    if (this->_index < this->_rows * this->_columns)
        return;

    throw ExceptionIndex(__FILE__, line);
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
void IteratorConst<Container, Class_T, T>::_check_data_expairing(const size_t line) const
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, line);
}

