#ifndef ITERATOR_H
#define ITERATOR_H

#include <ranges>
#include <memory>
#include <concepts>

template <typename T>
class MatrixRow;

template <typename T>
class Matrix;

template<typename T, template <typename> class Container>
concept ContainerRequires = std::is_same_v<Container<T>, Matrix<T>> || std::is_same_v<Container<T>, MatrixRow<T>>;

template<typename T = bool, template <typename> class Container = Matrix> requires ContainerRequires<T, Container>
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
    Iterator(const Iterator<T, Container>& iterator) = default;

    ~Iterator() noexcept = default;

    bool operator != (Iterator const& iterator) const;
    bool operator == (Iterator const& iterator) const;
    bool operator < (Iterator const& iterator) const;

    Iterator<T, Container> operator + (const int value) const;
    Iterator<T, Container> operator - (const int value) const;
    Iterator<T, Container> &operator += (const int value);
    Iterator<T, Container> &operator -= (const int value);
    Iterator<T, Container> &operator = (const Iterator<T, Container> &iterator);

    Iterator<T, Container>& operator++();
    Iterator<T, Container> operator++(int);
    Iterator<T, Container>& operator--();
    Iterator<T, Container> operator--(int);

    T& operator *();
    const T& operator *() const;
    T* operator->();
    const T* operator->() const;

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
