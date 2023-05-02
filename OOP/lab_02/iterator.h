#ifndef ITERATOR_H
#define ITERATOR_H

#include <ranges>
#include <memory>
#include <concepts>

#include "concepts.h"

template<template <typename> class Container, typename Class_T, typename T = Class_T> requires ContainerRequires<Container, Class_T, T>
class Iterator
{
public:
    const Container<Class_T> *range;
    T current;

    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;


    Iterator() = default;
    Iterator(Container<Class_T> &data, const size_t index = 0);
    Iterator(const Container<Class_T> &matrix, const size_t index = 0);
    Iterator(const Iterator<Container, Class_T, T>& iterator) = default;

    ~Iterator() noexcept = default;

    bool operator != (Iterator<Container, Class_T, T> const& iterator) const;
    bool operator == (Iterator<Container, Class_T, T> const& iterator) const;
    bool operator < (Iterator<Container, Class_T, T> const& iterator) const;

    Iterator<Container, Class_T, T> operator + (const int value);
    Iterator<Container, Class_T, T> operator - (const int value);
    Iterator<Container, Class_T, T> &operator += (const int value);
    Iterator<Container, Class_T, T> &operator -= (const int value);
    Iterator<Container, Class_T, T> &operator = (const Iterator<Container, Class_T, T> &iterator);

    Iterator<Container, Class_T, T>& operator++();
    Iterator<Container, Class_T, T> operator++(int);
    Iterator<Container, Class_T, T>& operator--();
    Iterator<Container, Class_T, T> operator--(int);

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
