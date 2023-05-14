#include "ObjectOnField.h"

ObjectOnField::ObjectOnField(std::string imagePath)
: _imagePath(imagePath) {}

ObjectOnField::ObjectOnField()
{
    _imagePath = paths.at("Empty");
}

ObjectOnField::~ObjectOnField() {}

std::string ObjectOnField::getImagePath() const
{
    return _imagePath;
}

void ObjectOnField::setImagePath(std::string imagePath)
{
    _imagePath = imagePath;
}