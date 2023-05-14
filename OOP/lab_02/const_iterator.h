#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <concepts>
#include <memory>
#include <ranges>

#include "concepts.h"

template<MatrixType T>
class IteratorConst
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;
    using iterator = IteratorConst<T>;

    IteratorConst() noexcept = default;
    IteratorConst(Matrix<T> &data, const size_t index = 0);
    IteratorConst(const Matrix<T> &matrix, const size_t index = 0);
    IteratorConst(const IteratorConst &iterator) = default;
    IteratorConst(IteratorConst &&iterator) noexcept = default;

    ~IteratorConst() noexcept = default;

    iterator &operator = (const iterator &other);
    iterator &operator = (iterator &&other) noexcept;

    bool operator != (iterator const& iterator) const;
    bool operator == (iterator const& iterator) const;
    bool operator < (iterator const& iterator) const;
    bool operator > (const iterator &it) const;
    bool operator <= (const iterator &it) const;
    bool operator >= (const iterator &it) const;

    iterator &operator -- ();
    iterator operator -- (int);
    iterator &operator -= (const size_t count);
    iterator operator - (const size_t count) const;
    difference_type operator - (const iterator &it);

    iterator &operator ++ ();
    iterator operator ++ (int);
    iterator &operator += (const size_t count);
    iterator operator + (const size_t count) const;

    T &operator *() const;
    T *operator->() const;

    T &operator[](const size_t index) const;
private:
    std::weak_ptr<T[]> _data;
    size_t _index = 0;
    size_t _size = 0;

    void _check_valid_index(const size_t line) const;
    void _check_data_expairing(const size_t line) const;
    void _increase(const size_t count);
    void _dicrease(const size_t count);
};

#include "const_iterator.hpp"
#endif // CONST_ITERATOR_H
