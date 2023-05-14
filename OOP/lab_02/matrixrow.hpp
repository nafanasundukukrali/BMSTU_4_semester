#include "matrix.h"
#include "concepts.h"
#include <ranges>
#include <algorithm>

//template<MatrixType T>
//Matrix<T>::MatrixRow::MatrixRow(const Matrix<T>& parent, size_t row)
//{
//    this->_parent = parent;
//    this->_row_number = row;
//    this->_columns = parent.get_columns_count();
//}

//template<MatrixType T>
//T& Matrix<T>::MatrixRow::operator[](size_t column)
//{
//    return this-> _parent._data.get()[column + this->_columns * this->_row_number];
//}

//template<MatrixType T>
//const T& Matrix<T>::MatrixRow::operator[](size_t column) const
//{
//    return this->_parent._data.get()[column + this->_columns * this->_row_number];
//}



//template<MatrixType T>
//MatrixRow<T>::MatrixRow(std::initializer_list<T> list): MatrixBase(1, list.size())
//{
//    this->_reallocate_data();

//    std::ranges::copy(list, this->begin());
//}

//template<MatrixType T>
//MatrixRow<T>::MatrixRow(const size_t columns):  MatrixBase(1, columns)
//{
//    this->_reallocate_data();
//}

//template<MatrixType T>
//MatrixRow<T>::MatrixRow(const MatrixRow<T> &row):  MatrixBase(1, row._columns)
//{
//    this->_reallocate_data();

//    std::ranges::copy(row, this->begin());
//}

//template<MatrixType T>
//MatrixRow<T>::MatrixRow(MatrixRow<T> &&row) noexcept: MatrixBase(1, row._columns)
//{
//    this->_data = row._data;
//}

//template<MatrixType T>
//template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
//requires std::constructible_from<T, typename std::iterator_traits<Iter>::reference>
//MatrixRow<T>::MatrixRow(Iter begin, Iter_e end)
//{
//    size_t size = 0;

//    for (auto iter = begin; iter != end; iter++, size++);
//    this->_rows = 1;
//    this->reset_data(new T[size], size);

//    std::ranges::copy(begin, end, this->begin());
//}

//template<MatrixType T>
//T& MatrixRow<T>::operator[](size_t column)
//{
//    if (this->_columns <= column)
//       throw ExceptionIndex(__FILE__,  __LINE__, "Column number is out of range.");

//    return this->_data[column];
//}

//template<MatrixType T>
//const T& MatrixRow<T>::operator[](size_t column) const
//{
//    if (this->_columns <= column)
//       throw ExceptionIndex(__FILE__,  __LINE__, "Column number is out of range.");

//    return this->_data[column];
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator = (MatrixRow<T>&& row)
//{
//    this->_columns = row._columns;
//    this->_data = row._data;

//    return *this;
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator = (const MatrixRow<T>& row)
//{
//    this->_columns = row._columns;

//    this->_reallocate_data();

//    std::ranges::copy(row, this->begin());

//    return *this;
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator = (MatrixRow<T>& row)
//{
//    this->_columns = row._columns;

//    this->_reallocate_data();

//    std::ranges::copy(row, this->begin());

//    return *this;
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator = (T *row)
//{
//    this->_validate_input_pointer(row, __LINE__);
//    this->_reallocate_data();

//    size_t i = 0;

//    for (auto &x: *this)
//    {
//       x = row[i];
//       i += 1;
//    }

//    return *this;
//}

//template<MatrixType T>
//void MatrixRow<T>::reset_data(T *data, size_t new_size)
//{
//    this->_columns = new_size;
//    this->_data.reset(data);
//}

//template<MatrixType T>
//bool MatrixRow<T>::operator == (const MatrixRow<T>& row) const
//{
//    return std::equal(this->begin(), this->end(), row.begin(), row.end());
//}

//template<MatrixType T>
//    MatrixRow<T> MatrixRow<T>::operator + (const MatrixRow<T>& row)
//{
//    row._validate_empty(__LINE__);
//    this->_validate_empty(__LINE__);
//    this->_validate_another_matrix_params(row._rows, row._columns, __LINE__);

//    MatrixRow<T> buffer(*this);

//    std::transform(buffer.begin(), buffer.end(), row.begin(), buffer.begin(),
//                   [](const auto left, const auto right) { return left + right; });

//    return buffer;
//}

//template<MatrixType T>
//    MatrixRow<T> MatrixRow<T>::operator - (const MatrixRow<T>& row)
//{
//    row._validate_empty(__LINE__);
//    this->_validate_empty(__LINE__);
//    this->_validate_another_matrix_params(row._rows, row._columns, __LINE__);

//    MatrixRow<T> buffer(*this);

//    std::transform(buffer.begin(), buffer.end(), row.begin(), buffer.begin(),
//                   [](const auto left, const auto right) { return left - right; });

//    return buffer;
//}

//template<MatrixType T>
//MatrixRow<T> MatrixRow<T>::operator * (const T value)
//{
//    this->_validate_empty(__LINE__);

//    MatrixRow<T> buffer(*this);

//    std::for_each(buffer.begin(), buffer.end(), [v = value](auto& el) mutable { el *= v; });

//    return buffer;
//}

//template<MatrixType T>
//MatrixRow<T> MatrixRow<T>::operator / (const T value)
//{
//    this->_validate_empty(__LINE__);

//    try
//    {
//       this->_data[0] / value;
//    }
//    catch (...)
//    {
//       throw ExceptionImpossibleOperation(__FILE__, __LINE__,
//                                          "Division is not availiable.");
//    }

//    MatrixRow<T> buffer(*this);

//    std::for_each(buffer.begin(), buffer.end(), [v = value](auto& el) mutable { el /= v; });

//    return buffer;
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator += (const MatrixRow<T>& row)
//{
//    *this = (*this) + row;

//    return *this;
//}

//template<MatrixType T>
//    MatrixRow<T>& MatrixRow<T>::operator -= (const MatrixRow<T>& row)
//{
//    *this = (*this) - row;

//    return *this;
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator *= (const T value)
//{
//    *this = (*this) * value;

//    return *this;
//}

//template<MatrixType T>
//MatrixRow<T>& MatrixRow<T>::operator /= (const T value)
//{
//    *this = (*this) / value;

//    return *this;
//}

//template<MatrixType T>
//void MatrixRow<T>::make_zero()
//{
//    this->_validate_empty(__LINE__);
//    std::transform(this->begin(), this->end(), this->begin(), [] (auto &x) {return 0;});
//}

//template<MatrixType T>
//void MatrixRow<T>::add_column(size_t post_position, T value)
//{
//    if (post_position > this->_columns)
//       throw ExceptionIndex(__FILE__,  __LINE__);

//    MatrixRow<T> buffer(this->_columns + 1);

//    std::ranges::copy(this->begin(), this->begin() + post_position, buffer.begin());

//    buffer[post_position] = value;

//    std::ranges::copy(this->begin() + size_t(post_position), this->end(), buffer.begin() + size_t(post_position + 1));

//    *this = buffer;
//}

//template<MatrixType T>
//void MatrixRow<T>::delete_column(size_t column_number)
//{
//    if (column_number >= this->_columns)
//       throw ExceptionIndex(__FILE__,  __LINE__);

//    MatrixRow<T> buffer(this->_columns - 1);

//    std::ranges::copy(this->begin(), this->begin() + column_number, buffer.begin());
//    std::ranges::copy(this->begin() + size_t(column_number + 1), this->end(), buffer.begin() + column_number);

//    *this = buffer;
//}

//template<MatrixType T>
//void MatrixRow<T>::_reallocate_data()
//{
//    try
//    {
//       this->_data.reset(new T[this->_columns]);
//    }
//    catch (std::bad_alloc)
//    {
//       throw ExceptionBadAllocate(__FILE__,  __LINE__);
//    }
//}

//template<MatrixType T>
//Iterator<MatrixRow, T> MatrixRow<T>::begin()
//{
//    return Iterator<MatrixRow, T>(*this, 0);
//}

//template<MatrixType T>
//Iterator<MatrixRow, T> MatrixRow<T>::end()
//{
//    return Iterator<MatrixRow, T>(*this, this->_columns);
//}

//template<MatrixType T>
//IteratorConst<MatrixRow, T> MatrixRow<T>::begin() const
//{
//    return IteratorConst<MatrixRow, T>(*this, 0);
//}

//template<MatrixType T>
//IteratorConst<MatrixRow, T> MatrixRow<T>::end() const
//{
//    return IteratorConst<MatrixRow, T>(*this, this->_columns);
//}

//template<MatrixType T>
//IteratorConst<MatrixRow, T> MatrixRow<T>::cbegin() const
//{
//    return IteratorConst<MatrixRow, T>(*this, 0);
//}

//template<MatrixType T>
//IteratorConst<MatrixRow, T> MatrixRow<T>::cend() const
//{
//    return IteratorConst<MatrixRow, T>(*this, this->_columns);
//}

//template<MatrixType T>
//size_t MatrixRow<T>::size() const
//{
//    return this->_rows * this->_columns;
//}
