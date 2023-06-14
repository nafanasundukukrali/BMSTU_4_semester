#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "object.h"

class Composite : public Object
{
public:
    Composite() = default;
    explicit Composite(const std::shared_ptr<Object> &component);
    explicit Composite(const std::vector<std::shared_ptr<Object>> &vector);
    bool isComposite() const override { return true; }
    virtual bool add(const std::shared_ptr<Object>&element) override;
    virtual bool remove(const iterator &iter) override;
//    iterator begin() const override;
//    iterator end() const override;

    bool add(const std::shared_ptr<Object> &component) override;

    bool remove(const Iterator &iterator) override;

    iterator begin() override;
    iterator end() override;

    const_iterator begin() const override;
    const_iterator end() const override;

    [[nodiscard]] ConstIterator cbegin() const override;
    [[nodiscard]] ConstIterator cend() const override;

    bool is_visible() override;

    [[nodiscard]] bool is_composite() const override;

    void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params) override;

    void accept(std::shared_ptr<Visitor> visitor) override;
private:

    std::vector<std::shared_ptr<Object>> _objects;
};

#endif // COMPOSITE_H
