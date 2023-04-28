#include "const_iterator.h"
#include "exceptionmatrix.h"

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T>::IteratorConst(const Container<T> &container, const size_t index)
{
    this->_index = index;
    this->_data.reset(container._data);
    this->_rows = container._rows;
    this->_columns = container.columns;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
bool IteratorConst<Container, T>::operator != (IteratorConst const& iterator) const
{
    return this->_index != iterator._index;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
bool IteratorConst<Container, T>::operator == (IteratorConst const& other) const
{
    return this->_index == other._index;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
bool IteratorConst<Container, T>::operator < (IteratorConst const& other) const
{
    return this->_index < other._index;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> IteratorConst<Container, T>::operator + (const int value)
{
   if (value < 0 && this->_index < static_cast<size_t>(-value))
       this->_index = 0;
   else
       this->_index++;

   if (this->_index > this->_rows * this->_columns)
       this->_index = this->_rows * this->_columns;

   return this;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> IteratorConst<Container, T>::operator - (const int value)
{
    return operator + (-value);
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> &IteratorConst<Container, T>::operator += (const int value)
{
    operator + (value);

    return *this;
}


template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> &IteratorConst<Container, T>::operator = (const IteratorConst<Container, T> &iterator)
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_columns = iterator._columns;

    return *this;
}


template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> &IteratorConst<Container, T>::operator ++()
{
    if (this->_index < this->_columns *this->_rows)
       this->_index++;

    return *this;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> IteratorConst<Container, T>::operator ++(int) const
{
    IteratorConst& buffer = *this;
    ++(*this);

    return buffer;
}


template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> &IteratorConst<Container, T>::operator --()
{
    if (this->_index > 0)
       this->_index--;

    return *this;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
IteratorConst<Container, T> IteratorConst<Container, T>::operator --(int) const
{
    IteratorConst& buffer = *this;
    --(*this);

    return buffer;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
T &IteratorConst<Container, T>::operator *() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
T *IteratorConst<Container, T>::operator ->() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
void IteratorConst<Container, T>::_check_valid_index(size_t line, std::string class_name)
{
    if (this->_index < this->_rows * this->_columns)
        return;

    throw ExceptionIndex(__FILE__, class_name, line);
}

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
void IteratorConst<Container, T>::_check_data_expairing(size_t line, std::string class_name)
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, class_name, line);
}

