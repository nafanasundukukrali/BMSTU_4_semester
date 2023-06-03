#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

class Object;

using PtrObject = std::vector<std::shared_ptr<Object>>;
using VectorComponent = std::vector<PtrObject>;

class Object {
public:
    using value_type = Object;
    using size_type = size_t;
    using iterator = PtrObject::const_iterator;
    using const_iterator = PtrObject::const_iterator;

    Object() = default;

    virtual ~Object() = default;

    // TODO
    //virtual void accept(std::shared_ptr<Visitor> visitor) = 0;

    virtual bool isComposite() const { return false; }
    virtual bool isVisible() { return false; }
    virtual bool add(const std::shared_ptr<Object> &) { return false; };
    virtual bool remove(const iterator &) { return false; };
    virtual iterator begin() { return iterator(); };
    virtual iterator end() { return iterator(); };
};

#endif // OBJECT_H
