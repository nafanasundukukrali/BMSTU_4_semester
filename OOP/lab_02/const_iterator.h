#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <concepts>
#include <memory>

#include "concepts.h"

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
class IteratorConst
{
public:
    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;

    IteratorConst(const Container<T> &container, const size_t index = 0);

    IteratorConst(const IteratorConst& iterator) = default;

    ~IteratorConst() noexcept = default;

    bool operator != (IteratorConst const& iterator) const;
    bool operator == (IteratorConst const& iterator) const;
    bool operator < (IteratorConst const& iterator) const;

    IteratorConst<Container, T> operator + (const int value);
    IteratorConst<Container, T> operator - (const int value);
    IteratorConst<Container, T> &operator += (const int value);
    IteratorConst<Container, T> &operator -= (const int value);
    IteratorConst<Container, T> &operator = (const IteratorConst<Container, T> &iterator);

    IteratorConst<Container, T>& operator++();
    IteratorConst<Container, T> operator++(int) const;
    IteratorConst<Container, T>& operator--();
    IteratorConst<Container, T> operator--(int) const;

    T& operator *() const;
    T* operator ->() const;

private:
    std::weak_ptr<T[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _columns = 0;

    void _check_valid_index(size_t line, std::string class_name);
    void _check_data_expairing(size_t line, std::string class_name);
};

#include "const_iterator.hpp"
#endif // CONST_ITERATOR_H
