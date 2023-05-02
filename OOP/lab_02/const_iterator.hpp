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
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator + (const int value)
{
   if (value < 0 && this->_index < static_cast<size_t>(-value))
       this->_index = 0;
   else
       this->_index++;

   if (this->_index > this->_rows * this->_columns)
       this->_index = this->_rows * this->_columns;

   return this;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator - (const int value)
{
    return operator + (-value);
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
IteratorConst<Container, Class_T, T> &IteratorConst<Container, Class_T, T>::operator += (const int value)
{
    operator + (value);

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
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator ++(int) const
{
    IteratorConst& buffer = *this;
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
IteratorConst<Container, Class_T, T> IteratorConst<Container, Class_T, T>::operator --(int) const
{
    IteratorConst& buffer = *this;
    --(*this);

    return buffer;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
T &IteratorConst<Container, Class_T, T>::operator *() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
T *IteratorConst<Container, Class_T, T>::operator ->() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
void IteratorConst<Container, Class_T, T>::_check_valid_index(const size_t line, const std::string class_name) const
{
    if (this->_index < this->_rows * this->_columns)
        return;

    throw ExceptionIndex(__FILE__, class_name, line);
}

template<template <typename> class Container, typename Class_T, typename T> requires ContainerRequires<Container, Class_T, T>
void IteratorConst<Container, Class_T, T>::_check_data_expairing(const size_t line, const std::string class_name) const
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, class_name, line);
}

