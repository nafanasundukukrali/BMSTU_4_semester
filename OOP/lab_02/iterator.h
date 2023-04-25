#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <concepts>

template <typename T>
class MatrixRow;

template <typename T>
class Matrix;

template <typename T>
class Iterator
{
public:
    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(const Matrix<T> &matrix, const size_t index = 0): _index(index),
                                                               _rows(matrix._rows),
                                                               _columns(matrix._columns) {}
    Iterator(const Iterator& iterator) = default;

    ~Iterator() noexcept = default;

    bool operator != (Iterator const& iterator) const;
    bool operator == (Iterator const& iterator) const;
    bool operator < (Iterator const& iterator) const;

    Iterator<T> operator + (const int value);
    Iterator<T> operator - (const int value);
    Iterator<T> &operator += (const int value);
    Iterator<T> &operator -= (const int value);
    Iterator<T> &operator = (const Iterator<T> &iterator);

    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T>& operator--();
    Iterator<T> operator--(int);

    T& operator *();
    const T& operator *() const;
    T* operator->();
    const T* operator->() const;

private:
    std::weak_ptr<MatrixRow<T>[]> _data = nullptr;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _columns = 0;

    void _check_valid_index(size_t line, std::string class_name);
    void _check_data_expairing(size_t line, std::string class_name);
};

#include "iterator.hpp"

#endif // ITERATOR_H
