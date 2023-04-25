#include "iterator.h"
#include "exceptionmatrix.h"

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container>::Iterator(const Container<T> &container, const size_t index)
{
    this->_index = index;
    this->_data = container._data;
    this->_rows = container._rows;
    this->_columns = container._columns;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
bool Iterator<T, Container>::operator != (Iterator const& iterator) const
{
    return this->_index != iterator._index;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
bool Iterator<T, Container>::operator == (Iterator const& other) const
{
    return this->_index == other._index;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
bool Iterator<T, Container>::operator < (Iterator const& other) const
{
    return this->_index < other._index;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> Iterator<T, Container>::operator + (const int value) const
{
    Iterator<T, Container> buffer(*this);
    if (value < 0 && this->_index < static_cast<size_t>(-value))
        this->_index = 0;
    else
        this->_index++;
    if (this->_index > this->_rows * this->_columns)
        this->_index = this->_rows * this->_columns;

   return buffer;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> Iterator<T, Container>::operator - (const int value) const
{
    return operator + (-value);
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> &Iterator<T, Container>::operator += (const int value)
{
    operator + (value);

    return *this;
}


template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> &Iterator<T, Container>::operator -= (const int value)
{
    operator - (value);

    return *this;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> &Iterator<T, Container>::operator = (const Iterator<T, Container> &iterator)
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_columns = iterator._columns;

    return *this;
}


template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> &Iterator<T, Container>::operator ++()
{
    if (this->_index < this->_columns *this->_rows)
       this->_index++;

    return *this;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> Iterator<T, Container>::operator ++(int)
{
    Iterator<T, Container> buffer(*this);
    ++(*this);

    return buffer;
}


template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> &Iterator<T, Container>::operator --()
{
    if (this->_index > 0)
       this->_index--;

    return *this;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
Iterator<T, Container> Iterator<T, Container>::operator --(int)
{
    Iterator<T, Container> buffer(*this);
    --(*this);

    return buffer;
}


template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
T &Iterator<T, Container>::operator *()
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
const T &Iterator<T, Container>::operator *() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return *(buffer.get() + this->_index);
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
T *Iterator<T, Container>::operator ->()
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
const T*Iterator<T, Container>::operator ->() const
{
    this->_check_data_expairing(__LINE__, typeid(*this).name());
    this->_check_valid_index(__LINE__, typeid(*this).name());

    std::shared_ptr<T[]> buffer = this->_data.lock();

    return buffer.get() + this->_index;
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
void Iterator<T, Container>::_check_valid_index(size_t line, std::string class_name)
{
    if (this->_index < this->_rows * this->_columns)
        return;

    throw ExceptionIndex(__FILE__, class_name, line);
}

template <typename T, template <typename> class Container> requires ContainerRequires<T, Container>
void Iterator<T, Container>::_check_data_expairing(size_t line, std::string class_name)
{
    if (!this->_data.expired())
        return;

    throw ExceptionDataExpaired(__FILE__, class_name, line);
}
