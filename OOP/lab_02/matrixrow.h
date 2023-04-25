#ifndef MATRIXROW_H
#define MATRIXROW_H
#include "iterator.h"
#include "const_iterator.h"
#include <memory>
#include "exceptionmatrix.h"
#include "matrixbase.h"

template <typename T>
class MatrixRow: public MatrixBase
{
    friend Iterator<T, MatrixRow>;
    friend IteratorConst<T, MatrixRow>;
public:
    MatrixRow(): MatrixBase(1, 0), _data(nullptr) {};
    explicit MatrixRow(T* data, size_t size): MatrixBase(1, size), _data(data) {}
    MatrixRow(Iterator<T, MatrixRow> begin, Iterator<T, MatrixRow> end);
    T& operator [] (size_t column);
    const T& operator [] (size_t column) const;
    void reset_data(T* data, size_t new_size);
    T& operator * () const;

    Iterator<T, MatrixRow> begin();
    Iterator<T, MatrixRow> end();
    IteratorConst<T, MatrixRow> begin() const;
    IteratorConst<T, MatrixRow> end() const;
    IteratorConst<T, MatrixRow> cbegin() const;
    IteratorConst<T, MatrixRow> cend() const;
//    Iterator<T, MatrixRow> rbegin();
//    Iterator<T, MatrixRow> rend();
//    IteratorConst<T, MatrixRow> rbegin() const;
//    IteratorConst<T, MatrixRow> rend() const;
//    IteratorConst<T, MatrixRow> crbegin() const;
//    IteratorConst<T, MatrixRow> crend() const;
private:
    std::shared_ptr<T[]> _data = nullptr;
};
template <typename T>
inline constexpr bool std::ranges::enable_borrowed_range<MatrixRow<T>> = true;

template <typename T>
static_assert(std::input_range<MatrixRow<T>>);

#include "matrixrow.hpp"

#endif // MATRIXROW_H
