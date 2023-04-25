#ifndef MATRIXROW_H
#define MATRIXROW_H
#include "iterator.h"
#include "const_iterator.h"
#include <memory>
#include "exceptionmatrix.h"

template <typename T>
class Matrix;

template <typename T>
class MatrixRow
{
    friend Iterator<T>;
    friend IteratorConst<T>;
    friend Matrix<T>;
public:
    MatrixRow() = default;
    MatrixRow(T* data, size_t size) : _data(data), _size(size) {}
    T& operator [] (size_t column);
    const T& operator [] (size_t column) const;
    void reset_data(T* data, size_t new_size);

    Iterator<T> begin();
    Iterator<T> end();
    IteratorConst<T> begin() const;
    IteratorConst<T> end() const;
    IteratorConst<T> cbegin() const;
    IteratorConst<T> cend() const;
    Iterator<T> rbegin();
    Iterator<T> rend();
    IteratorConst<T> rbegin() const;
    IteratorConst<T> rend() const;
    IteratorConst<T> crbegin() const;
    IteratorConst<T> crend() const;
private:
    std::shared_ptr<T[]> _data = nullptr;
    size_t _size = 0;
};

#include "matrixrow.hpp"

#endif // MATRIXROW_H
