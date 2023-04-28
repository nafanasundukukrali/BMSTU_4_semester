#ifndef MATRIXROW_H
#define MATRIXROW_H
#include "iterator.h"
#include "const_iterator.h"
#include <memory>
#include "matrixbase.h"

template <typename T>
class MatrixRow: public MatrixBase
{
    friend Iterator<MatrixRow, T>;
    friend IteratorConst<MatrixRow, T>;
public:
    explicit MatrixRow(): MatrixBase(1, 0), _data(nullptr) {};
    explicit MatrixRow(T* data, size_t size): MatrixBase(1, size), _data(data) {}
    explicit MatrixRow(std::initializer_list<std::initializer_list<T>> list);
    T& operator [] (size_t column);
    const T& operator [] (size_t column) const;
    void reset_data(T* data, size_t new_size);
    T& operator * () const;

    MatrixRow<T>& operator = (const MatrixRow<T>& matrix);
    MatrixRow<T>& operator = (MatrixRow<T>&& matrix);
    MatrixRow<T>& operator = (std::initializer_list<std::initializer_list<T>> list);

    template<typename U> requires FloatingType<U> && std::same_as<T, U>
    MatrixRow<T>& operator += (const MatrixRow<T>& matrix);
    template<typename U> requires FloatingType<U> && std::same_as<T, U>
    MatrixRow<T>& operator -= (const MatrixRow<T>& matrix);
    template<typename U> requires FloatingType<U> && std::same_as<T, U>
    MatrixRow<T>& operator *= (const MatrixRow<T>& matrix);
    MatrixRow<T>& operator *= (const T value);

    Iterator<MatrixRow, T> begin();
    Iterator<MatrixRow, T> end();
    IteratorConst<MatrixRow, T> begin() const;
    IteratorConst<MatrixRow, T> end() const;
    IteratorConst<MatrixRow, T> cbegin() const;
    IteratorConst<MatrixRow, T> cend() const;
    Iterator<MatrixRow, T> rbegin();
    Iterator<MatrixRow, T> rend();
    IteratorConst<MatrixRow, T> rbegin() const;
    IteratorConst<MatrixRow, T> rend() const;
    IteratorConst<MatrixRow, T> crbegin() const;
    IteratorConst<MatrixRow, T> crend() const;
private:
    std::shared_ptr<T[]> _data = nullptr;
};

#include "matrixrow.hpp"

#endif // MATRIXROW_H
