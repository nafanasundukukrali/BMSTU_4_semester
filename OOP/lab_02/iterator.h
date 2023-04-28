#ifndef ITERATOR_H
#define ITERATOR_H

#include <ranges>
#include <memory>
#include <concepts>

#include "concepts.h"

template<template <typename U> class Container, typename T> requires ContainerRequires<Container, T>
class Iterator
{
public:
    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator() = default;
    Iterator(const Container<T> &matrix, const size_t index = 0);
    Iterator(const Iterator<Container, T>& iterator) = default;

    ~Iterator() noexcept = default;

    bool operator != (Iterator const& iterator) const;
    bool operator == (Iterator const& iterator) const;
    bool operator < (Iterator const& iterator) const;

    Iterator<Container, T> operator + (const int value);
    Iterator<Container, T> operator - (const int value);
    Iterator<Container, T> &operator += (const int value);
    Iterator<Container, T> &operator -= (const int value);
    Iterator<Container, T> &operator = (const Iterator<Container, T> &iterator);

    Iterator<Container, T>& operator++();
    Iterator<Container, T> operator++(int);
    Iterator<Container, T>& operator--();
    Iterator<Container, T> operator--(int);

    T& operator *();
    T& operator *() const;
    T* operator->();
    T* operator->() const;

private:
    std::weak_ptr<T[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _columns = 0;

    void _check_valid_index(size_t line, std::string class_name);
    void _check_data_expairing(size_t line, std::string class_name);
};

#include "iterator.hpp"

#endif // ITERATOR_H
