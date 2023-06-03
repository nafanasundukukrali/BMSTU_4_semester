#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <utility>

#include "object.h"
#include "basemodel.h"
#include "point.h"
#include "edge.h"
#include "modeldata.h"

class Model : public BaseModel {
    friend class TransformVisitor;
public:
    Model() : _modelData(new ModelData) {};
    explicit Model(const std::shared_ptr<ModelData> &modelData) : _modelData(modelData) {};
    Model(const Model &model);

    ~Model() override = default;

    //virtual Point getCenter() const override;
    //virtual void accept(shared_ptr<ObjectVisitor> &) override;

    std::shared_ptr<ModelData> getModel() {return _modelData;}
    std::unique_ptr<BaseModel> clone() const;

protected:
    std::shared_ptr<ModelData> _modelData;
};

#endif // MODEL_H
