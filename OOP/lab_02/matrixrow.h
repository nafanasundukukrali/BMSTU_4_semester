#ifndef MATRIXROW_H
#define MATRIXROW_H
#include "iterator.h"
#include "const_iterator.h"
#include <memory>
#include "matrixbase.h"
#include <concepts.h>

template <MatrixType T>
class MatrixRow: public MatrixBase
{
    friend Iterator<MatrixRow, T>;
    friend IteratorConst<MatrixRow, T>;
public:
    using iterator = Iterator<MatrixRow, T>;
    using const_iterator = IteratorConst<MatrixRow, T>;
    using difference_type = typename Iterator<MatrixRow, T>::difference_type;
    using reference = typename Iterator<MatrixRow, T>::reference;
    using const_reference = typename IteratorConst<MatrixRow, T>::reference;
    using pointer = typename Iterator<MatrixRow, T>::pointer;
    using const_pointer = typename Iterator<MatrixRow, T>::pointer;

    explicit MatrixRow(): MatrixBase(1, 0), _data(nullptr) {};
    explicit MatrixRow(const size_t size);
    MatrixRow(T* data, size_t size): MatrixBase(1, size), _data(data) {}
    explicit MatrixRow(const MatrixRow<T> &row);
    MatrixRow(MatrixRow<T> &&row) noexcept;
    template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
    requires std::constructible_from<T, typename std::iterator_traits<Iter>::reference>
    MatrixRow(Iter begin, Iter_e end);
    MatrixRow(std::initializer_list<T> list);

    ~MatrixRow() noexcept = default;

    bool operator == (const MatrixRow<T>& row) const;

    MatrixRow<T>& operator = (const MatrixRow<T>& row);
    MatrixRow<T>& operator = (MatrixRow<T>& row);
    MatrixRow<T>& operator = (MatrixRow<T>&& row);
    MatrixRow<T>& operator = (T *row);

    MatrixRow<T>& operator += (const MatrixRow<T>& row);
    MatrixRow<T> operator + (const MatrixRow<T>& row);

    MatrixRow<T>& operator -= (const MatrixRow<T>& row);
    MatrixRow<T> operator - (const MatrixRow<T>& row);

    MatrixRow<T>& operator *= (const T value);
    MatrixRow<T> operator * (const T value);

    MatrixRow<T>& operator /= (const T value);
    MatrixRow<T> operator / (const T value);

    T& operator [] (size_t column);
    const T& operator [] (size_t column) const;

    T& operator * () const;

    void make_zero();

    void add_column(size_t post_position, T value);
    void delete_column(size_t column_position);

    Iterator<MatrixRow, T> begin();
    Iterator<MatrixRow, T> end();
    IteratorConst<MatrixRow, T> begin() const;
    IteratorConst<MatrixRow, T> end() const;
    IteratorConst<MatrixRow, T> cbegin() const;
    IteratorConst<MatrixRow, T> cend() const;

    size_t size() const;
    size_t get_rows_count() const { return 1; };
    void reset_data(T* data, size_t new_size);
private:
    std::shared_ptr<T[]> _data = nullptr;
    void _reallocate_data();
};

#include "matrixrow.hpp"

#endif // MATRIXROW_H
