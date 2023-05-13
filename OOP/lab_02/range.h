#ifndef RANGE_H
#define RANGE_H

#include "iterator.h"
#include "const_iterator.h"
#include "concepts.h"

template <MatrixType FROM, MatrixType TO>
class Range
{
public:
    class iterator
    {
    private:
        int num = FROM;

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = int;
        using difference_type = int;
        using pointer = const int*;
        using reference = const int&;

        explicit iterator(long nm = 0) : num(nm) {}
        iterator& operator ++() { num += FROM <= TO ? 1 : -1; return *this; }
        iterator operator ++(int) { iterator retval = *this; ++(*this); return retval; }
        bool operator ==(iterator other) const { return num == other.num; }
        bool operator !=(iterator other) const { return !(*this == other); }
        reference operator*() const { return num; }
    };

    iterator begin() { return iterator(FROM); }
    iterator end() { return iterator(FROM <= TO ? TO + 1 : TO - 1); }
};

#endif // RANGE_H
