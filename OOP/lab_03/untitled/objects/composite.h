#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "object.h"

class Composite : public Object
{
public:
    Composite() = default;
    Composite(PtrObject first, ...);
    bool isComposite() const override { return true; }
    virtual bool add(const std::shared_ptr<Object>&element) override;
    virtual bool remove(const iterator &iter) override;
//    iterator begin() const override;
//    iterator end() const override;
private:
    std::vector<std::shared_ptr<Object>> _objects;
};

#endif // COMPOSITE_H
