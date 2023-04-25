#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <concepts>
#include <memory>

template <typename T>
class MatrixRow;

template <typename T>
class Matrix;

template<typename T, template <typename> class Container>
concept ContainerRequires = requires(Container<T> cl) {cl._data; cl._rows; cl._columns;} ||
    requires(Container<T> cl) {cl._data; cl._size;};

template<typename T, template <typename> class Container> requires ContainerRequires<T, Container>
class IteratorConst
{
private:
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

    IteratorConst<T, Container> operator + (const int value);
    IteratorConst<T, Container> operator - (const int value);
    IteratorConst<T, Container> &operator += (const int value);
    IteratorConst<T, Container> &operator -= (const int value);
    IteratorConst<T, Container> &operator = (const IteratorConst<T, Container> &iterator);

    IteratorConst<T, Container>& operator++();
    IteratorConst<T, Container> operator++(int) const;
    IteratorConst<T, Container>& operator--();
    IteratorConst<T, Container> operator--(int) const;

    const T& operator *() const;
    const T* operator ->() const;

private:
    std::weak_ptr<T[]> _data = nullptr;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _columns = 0;

    void _check_valid_index(size_t line, std::string class_name);
    void _check_data_expairing(size_t line, std::string class_name);
};

#include "const_iterator.hpp"
#endif // CONST_ITERATOR_H
