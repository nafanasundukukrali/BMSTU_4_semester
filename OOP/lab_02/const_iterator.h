#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <concepts>
#include <memory>
#include <ranges>

#include "concepts.h"

template<template <typename> class Container, typename Class_T, typename T = Class_T> requires ContainerRequires<Container, Class_T, T>
class IteratorConst
{
public:
    const Container<Class_T> *range;
    T current;

    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;

    IteratorConst(const Container<Class_T> &container, const size_t index = 0);

    IteratorConst(const IteratorConst<Container, Class_T, T>& iterator) = default;

    ~IteratorConst() noexcept = default;

    bool operator != (IteratorConst<Container, Class_T, T> const& iterator) const;
    bool operator == (IteratorConst<Container, Class_T, T> const& iterator) const;
    bool operator < (IteratorConst<Container, Class_T, T> const& iterator) const;

    IteratorConst<Container, Class_T, T> operator + (const int value);
    IteratorConst<Container, Class_T, T> operator - (const int value);
    IteratorConst<Container, Class_T, T> &operator += (const int value);
    IteratorConst<Container, Class_T, T> &operator -= (const int value);
    IteratorConst<Container, Class_T, T> &operator = (const IteratorConst<Container, Class_T, T> &iterator);

    IteratorConst<Container, Class_T, T>& operator++();
    IteratorConst<Container, Class_T, T> operator++(int) const;
    IteratorConst<Container, Class_T, T>& operator--();
    IteratorConst<Container, Class_T, T> operator--(int) const;

    T& operator *() const;
    T* operator ->() const;

private:
    std::weak_ptr<T[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _columns = 0;

    void _check_valid_index(const size_t line, const std::string class_name) const;
    void _check_data_expairing(const size_t line, const std::string class_name) const;
};

#include "const_iterator.hpp"
#endif // CONST_ITERATOR_H
