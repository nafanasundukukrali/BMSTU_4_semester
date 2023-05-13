#include <ranges>
#include <concepts>
#include <numeric>
#include <algorithm>
#include "matrix.h"
#include "exceptionmatrix.h"

template<MatrixType T>
Matrix<T>::Matrix(const size_t rows, const size_t columns, const bool is_unit_matrix): MatrixBase(rows, columns)
{
    if (rows == 0 || columns == 0)
        throw ExceptionIndex(__FILE__,  __LINE__, "Matrix params incorrect.");

    if (rows != columns && is_unit_matrix)
        throw ExceptionImpossibleOperation(__FILE__,  __LINE__, "Not square matrix can't be unit.");

    this->_reallocate_data();

    std::ranges::for_each(*this, [] (auto &row) {row.make_zero();});

    if (is_unit_matrix) for (size_t i = 0; i < this->_columns; i++) this->_data[i][i] = 1;
}

template<MatrixType T>
Matrix<T>::Matrix(const Matrix<T> &matrix): MatrixBase(matrix._rows, matrix._columns)
{
    this->_reallocate_data();

    for (auto iter_1 = this->begin(), iter_2 = matrix.begin();
         iter_1 != this->end(); iter_1++, iter_2++)
        std::ranges::copy((*iter_2).begin(), (*iter_2).end(), (*iter_1).begin());
}

template<MatrixType T>
template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
requires std::constructible_from<MatrixRow<T>, typename std::iterator_traits<Iter>::reference>
Matrix<T>::Matrix(const Iter begin, const Iter_e end): MatrixBase()
{
    size_t size_rows = 0, size_columns = 0;

    for (auto iter = begin; iter != end; iter++, size_rows++);
    for (auto iter = (*begin).begin(); iter != (*begin).end(); iter++, size_columns++);

    this->_columns = size_columns;
    this->_rows = size_rows;
    this->_reallocate_data();

    for (auto iter = this->begin(), iter_2 = begin; iter != this->end(); iter++, iter_2++)
    {
        MatrixRow<T> buffer_row((*iter_2).begin(), (*iter_2).end());
        (*iter) = buffer_row;
    }
}

template<MatrixType T>
Matrix<T>::Matrix(Matrix<T> &&matrix) noexcept: MatrixBase(matrix._rows, matrix._columns)
{
    this->_data = matrix._data;
}

template<MatrixType T>
Matrix<T>::Matrix(T** array, const size_t rows, const size_t columns): MatrixBase(rows, columns)
{
    this->_validate_input_pointer(array);
    this->_reallocate_data();

    size_t i = 0;

    for (auto &row: *this)
        row = array[i];
}

template<MatrixType T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list): MatrixBase(list.size(), list.begin()->size())
{
    this->_reallocate_data();

    size_t i = 0;

    this->_copy_data_from_another_range(list);
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;

    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        std::ranges::copy(matrix._data[i].begin(), matrix._data[i].end(), this->_data[i].begin());

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;
    this->_data = matrix._data;

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>& matrix)
{
    this->_rows = matrix._rows;
    this->_columns = matrix._columns;

    this->_reallocate_data();

    for (size_t i = 0; i < this->_rows; i++)
        std::ranges::copy(matrix._data[i].begin(), matrix._data[i].end(), this->_data[i].begin());

    return *this;
}

template<MatrixType T>
bool Matrix<T>::is_square()
{
    return this->_columns == this->_rows && this->_rows != 0;
}

template<MatrixType T>
bool Matrix<T>::is_unit()
{
    if (!this->is_square())
        return false;

    for (size_t i = 0; i < this->_columns; i++)
        for (size_t j = 0; j < this->_columns; j++)
            if ((*this)[i][j] != (*this)[i][j] ||
                i != j && (*this)[i][j] != 0 ||
                i == j && (*this)[i][j] == 0)
                return false;

    return true;
}

template<MatrixType T>
T Matrix<T>::_calc_determinant()
{
    Matrix<T> U(*this);
    Matrix<T> L(this->_rows, this->_columns);

    for (size_t i = 0; i < this->_columns; i++)
        for (size_t j = i; j < this->_columns; j++)
            try
            {
                L[j][i]=U[j][i]/U[i][i];
            }
            catch (...)
            {
                ExceptionImpossibleToDivide(__FILE__, __LINE__);
            }

    for(size_t k = 1; k < this->_columns; k++)
    {
        for(size_t i = k-1; i < this->_columns; i++)
            for(size_t j = i; j < this->_columns; j++)
                try
                {
                    L[j][i]=U[j][i]/U[i][i];
                }
                catch (...)
                {
                    ExceptionImpossibleToDivide(__FILE__, __LINE__);
                }

        for(size_t i = k; i < this->_columns; i++)
            for(size_t j = k-1; j < this->_columns; j++)
                U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j];
    }

    T prov = U[0][0];

    for (size_t i = 1; i < this->_columns; i++)
        prov *= U[i][i];

    return prov;
}

template<MatrixType T>
Matrix<T> Matrix<T>::transpose()
{
    if (!this->is_square())
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "This matrix is not square, transposition is not availiable.");

    Matrix<T> buffer(*this);

    for (size_t i = 0; i < this->_columns; i++)
        for (size_t j = i + 1; j < this->_columns; j++)
            std::swap(buffer[i][j], buffer[j][i]);

    return buffer;
}

template<MatrixType T>
Matrix<T> Matrix<T>::inverse()
{
    if (!this->is_square() || this->_calc_determinant() == 0)
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "Transposition is not availiable.");

    Matrix<T> buffer_1 = (*this) * this->transpose();

    if (buffer_1.is_unit())
        throw ExceptionImpossibleOperation(__FILE__, __LINE__,
                                           "Transposition is not availiable.");

    Matrix<T> buffer(*this), result(this->_columns, this->_columns, true);

    for (size_t j = 0; j < this->_columns; j++) {
        if (buffer[j][j] == 0)
        {
            size_t k = j;

            for (; k < this->_columns && buffer[j][k] == 0; k++);

            std::swap(buffer[j], buffer[k]);
        }

        T divide = buffer[j][j];

        buffer[j] /= divide, result[j] /= divide;

        for (size_t i = 0; i < this->_columns; i++) {
            if (i == j)
                continue;

            T buf_1 = buffer[i][j];

            for (size_t k = 0; k < this->_columns; k++) {
                buffer[i][k] -= buf_1 * buffer[j][k];
                result[i][k] -= buf_1 * result[j][k];
            }
        }
    }

    return result;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator = (std::initializer_list<std::initializer_list<T>> list)
{
    this->_rows = list.size();
    this->_rows = list.begin->size();

    this->_reallocate_data();
    this->_copy_data_from_another_range(list);

    return *this;
}

template<MatrixType T>
bool Matrix<T>::operator == (const Matrix<T>& matrix) const
{
    return std::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<MatrixType T>
bool Matrix<T>::operator != (const Matrix<T>& matrix) const
{
    return !std::ranges::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

template<MatrixType T>
MatrixRow<T>& Matrix<T>::operator [] (const size_t row)
{
    if (this->_rows <= row)
        throw ExceptionIndex(__FILE__,  __LINE__, "Icorrect row index.");

    return this->_data[row];
}

template<MatrixType T>
const MatrixRow<T>& Matrix<T>::operator [] (const size_t row) const
{
    if (this->_rows <= row)
        throw ExceptionIndex(__FILE__, __LINE__, "Icorrect row index.");

    return this->_data[row];
}

template<MatrixType T>
T &Matrix<T>::operator()(size_t row, size_t col)
{
    return this->_data[row][col];
}

template<MatrixType T>
const T &Matrix<T>::operator()(size_t row, size_t col) const
{
    return this->_data[row][col];
}

template<MatrixType T>
Matrix<T> Matrix<T>::sum(const Matrix<T>& matrix)
{
    this->_validate_another_matrix_params(matrix._rows, matrix._columns, __LINE__);

    Matrix<T> buffer(*this);

    std::transform(buffer.begin(), buffer.end(), matrix.begin(), buffer.begin(),
                   [](auto &left, auto &right) { return left + right; });

    return buffer;
}

template<MatrixType T>
Matrix<T> Matrix<T>::sub(const Matrix<T>& matrix)
{
    this->_validate_another_matrix_params(matrix._rows, matrix._columns, __LINE__);

    Matrix<T> buffer(*this);

    std::transform(buffer.begin(), buffer.end(), matrix.begin(), buffer.begin(),
                   [](auto &left, auto &right) { return left - right; });

    return buffer;
}

template<MatrixType T>
Matrix<T> Matrix<T>::mul(const Matrix<T>& matrix)
{
    if (this->_columns != matrix._rows)
        throw ExceptionImpossibleOperation(__FILE__,  __LINE__, "Incorrect count of rows vs columns for mul.");

    Matrix<T> buffer(this->_rows, matrix._columns);

    for (size_t i = 0; i < buffer._columns; i++)
    {
        MatrixRow<T> buffer_column;

        buffer_column.reset_data(new T[matrix._rows], matrix._rows);

        std::transform(matrix.begin(), matrix.end(), buffer_column.begin(),
                       [matrix, i] (auto &row_1) {return row_1[i];});

        for (size_t j = 0; j < buffer._rows; j++)
            buffer[j][i] = std::inner_product(buffer_column.begin(), buffer_column.end(), (*this)[j].begin(), 0);
    }

    return buffer;
}

template<MatrixType T>
Matrix<T> Matrix<T>::div(const Matrix<T>& matrix)
{
    if (this->_columns != matrix._rows)
        throw ExceptionImpossibleOperation(__FILE__,  __LINE__, "Incorrect count of rows vs columns for div.");

    Matrix<T> buffer = matrix.inverse(), buffer_1(*this);
    buffer_1 *= buffer;

    return buffer_1;
}

template<MatrixType T>
Matrix<T> Matrix<T>::mul(const T value)
{
    this->_validate_empty(__LINE__);

    Matrix<T> buffer(*this);

    for (auto &row: buffer) row *= value;

    return buffer;
}

template<MatrixType T>
Matrix<T> Matrix<T>::div(const T value)
{
    this->_validate_empty(__LINE__);

    Matrix<T> buffer(*this);

    for (auto &row: buffer) row /= value;

    return buffer;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& matrix)
{
    *this = this->sum(matrix);

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& matrix)
{
    *this = this->sub(matrix);

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& matrix)
{
    *this = this->mul(matrix);
    this->_columns = matrix._columns;

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator *= (const T value)
{
    *this = this->mul(value);

    return *this;
}

template<MatrixType T>
Matrix<T>& Matrix<T>::operator /= (const T value)
{
    *this = this->div(value);

    return *this;
}

template<MatrixType T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& matrix)
{
    return this->sum(matrix);
}

template<MatrixType T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& matrix)
{
    return this->sub(matrix);
}

template<MatrixType T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& matrix)
{
    return this->mul(matrix);
}

template<MatrixType T>
Matrix<T> Matrix<T>::operator / (const Matrix<T>& matrix)
{
    return this->div(matrix);
}

template<MatrixType T>
void Matrix<T>::change_columns(size_t from_position, size_t to_position)
{
    if (this->_columns <= from_position || this->_columns <= to_position)
        throw ExceptionIndex(__FILE__,  __LINE__, "Inccorect input positions.");

    for (auto &row: *this)
        std::swap(row[from_position], row[to_position]);
}

template<MatrixType T>
void Matrix<T>::change_rows(size_t from_position, size_t to_position)
{
    if (this->_rows <= from_position || this->_rows <= to_position)
        throw ExceptionIndex(__FILE__,  __LINE__, "Inccorect input positions.");

    std::swap_ranges(this->_data[from_position].begin(),
                     this->_data[from_position].end(),
                     this->_data[to_position].begin());
}

template<MatrixType T>
void Matrix<T>::add_column(size_t post_column_number, std::initializer_list<T> list)
{
    if (this->_columns < post_column_number || list.size() != this->_rows)
        throw ExceptionIndex(__FILE__,  __LINE__, "Inccorect input positions.");

    size_t list_i = 0;

    for (auto &row: *this)
    {
        row.add_column(post_column_number, *(list.begin() + list_i));
        list_i++;
    }

    this->_columns++;
}

template<MatrixType T>
void Matrix<T>::add_row(size_t post_row_number, std::initializer_list<T> list)
{
    if (list.size() != this->_columns || this->_rows < post_row_number)
        throw ExceptionIndex(__FILE__,  __LINE__, "Inccorect input positions.");

    Matrix<T> buffer(this->_rows + 1, this->_columns);

    std::ranges::copy(this->begin(), this->begin() + post_row_number, buffer.begin());

    buffer[post_row_number] = list;

    std::ranges::copy(this->begin() + size_t(post_row_number), this->end(), buffer.begin() + size_t(post_row_number+ 1));

    *this = buffer;
}

template<MatrixType T>
void Matrix<T>::delete_column(size_t delete_column_number)
{
    if (this->_columns <= delete_column_number)
        throw ExceptionIndex(__FILE__,  __LINE__, "Inccorect input positions.");

    for (auto &row: *this)
        row.delete_column(delete_column_number);

    this->_columns--;
}

template<MatrixType T>
void Matrix<T>::delete_row(size_t delete_row_number)
{
    if (this->_rows <= delete_row_number)
        throw ExceptionIndex(__FILE__,  __LINE__, "Inccorect input positions.");

    Matrix<T> buffer(this->_rows - 1, this->_columns);

    std::ranges::copy(this->begin(), this->begin() + delete_row_number, buffer.begin());
    std::ranges::copy(this->begin() + size_t(delete_row_number + 1), this->end(), buffer.begin() + delete_row_number);

    *this = buffer;
}

template<MatrixType T>
size_t Matrix<T>::get_rows_count() const
{
    return this->_rows;
}

template<MatrixType T>
Matrix<T> Matrix<T>::operator * (const T value)
{
    return this->mul(value);
}

template<MatrixType T>
Iterator<Matrix, T, MatrixRow<T>> Matrix<T>::begin()
{
    return Iterator<Matrix, T, MatrixRow<T>>(*this, size_t(0));
}

template<MatrixType T>
Iterator<Matrix, T, MatrixRow<T>> Matrix<T>::end()
{
    return Iterator<Matrix, T, MatrixRow<T>>(*this, this->_rows);
}

template<MatrixType T>
IteratorConst<Matrix, T, MatrixRow<T>> Matrix<T>::begin() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, 0);
}

template<MatrixType T>
IteratorConst<Matrix, T, MatrixRow<T>>  Matrix<T>::end() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, this->_rows);
}

template<MatrixType T>
IteratorConst<Matrix, T, MatrixRow<T>>  Matrix<T>::cbegin() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, 0);
}

template<MatrixType T>
IteratorConst<Matrix, T, MatrixRow<T>> Matrix<T>::cend() const
{
    return IteratorConst<Matrix, T, MatrixRow<T>>(*this, this->_rows);
}

template<MatrixType T>
void Matrix<T>::_reallocate_data()
{
    try
    {
        this->_data.reset(new MatrixRow<T>[this->_rows]);

        for (size_t i = 0; i < this->_rows; i++)
            this->_data[i].reset_data(new T[this->_columns], this->_columns);
    }
    catch (std::bad_alloc)
    {
        throw ExceptionBadAllocate(__FILE__, __LINE__);
    }
}

template<MatrixType T>
void Matrix<T>::_copy_data_from_another_range(auto &range)
{
    size_t i = 0;

    for (auto &iter: range)
        if (this->_columns != iter.size())
        {
            throw ExceptionIndex(__FILE__, __LINE__, "Error of list element.");
        }
        else
        {
            std::ranges::copy(iter, this->_data[i].begin());
            i++;
        }
}
