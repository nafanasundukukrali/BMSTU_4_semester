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
    MatrixRow(T* data, size_t size): MatrixBase(1, size), _data(data) {}
    explicit MatrixRow(const MatrixRow<T> &row);
    MatrixRow(MatrixRow<T> &&row);
    MatrixRow(std::initializer_list<T> list);

    T& operator [] (size_t column);
    const T& operator [] (size_t column) const;
    void reset_data(T* data, size_t new_size);
    T& operator * () const;

    bool operator == (const MatrixRow<T>& row) const;

    MatrixRow<T>& operator = (const MatrixRow<T>& row);
    MatrixRow<T>& operator = (MatrixRow<T>&& row);


    MatrixRow<T>& operator += (const MatrixRow<T>& row);
    MatrixRow<T> operator + (const MatrixRow<T>& row);

    MatrixRow<T>& operator -= (const MatrixRow<T>& row);
    MatrixRow<T> operator - (const MatrixRow<T>& row);

    MatrixRow<T>& operator *= (const T value);
    MatrixRow<T> operator * (const T value);

    void add_column(size_t post_position, T value);
    void delete_column(size_t column_position);

    Iterator<MatrixRow, T> begin();
    Iterator<MatrixRow, T> end();
    IteratorConst<MatrixRow, T> begin() const;
    IteratorConst<MatrixRow, T> end() const;
    IteratorConst<MatrixRow, T> cbegin() const;
    IteratorConst<MatrixRow, T> cend() const;
    size_t size() const;
private:
    std::shared_ptr<T[]> _data = nullptr;
    void _reallocate_data();
};

static_assert(std::ranges::bidirectional_range<MatrixRow<int>>);

#include "matrixrow.hpp"

#endif // MATRIXROW_H
