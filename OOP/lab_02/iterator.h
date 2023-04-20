#include <memory>

#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
using SharedPtr = std::shared_ptr<T>;
template <typename T>
using WeakPtr = std::weak_ptr<T>;


class Iterator
{
public:
    Iterator();
};

#endif // ITERATOR_H
