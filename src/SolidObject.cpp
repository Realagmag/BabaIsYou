#include "SolidObject.h"

SolidObject::SolidObject(std::string imagePath) : ObjectOnField(imagePath)
{ _type = "SolidObject"; }

SolidObject::SolidObject() : ObjectOnField()
{ _type = "SolidObject"; }

std::string SolidObject::getImagePath() const
{
    if (_temporaryImagePath != "")
        return _temporaryImagePath;
    return _imagePath;
}

std::string SolidObject::getType() const
{
    if (_temporaryType != "")
        return _temporaryType;
    return _type;
}

ObjectOnFieldPtr SolidObject::getTemporaryIdentity() const
{
    return _temporaryIdentity;
}

void SolidObject::setTemporaryIdentity(const ObjectOnFieldPtr &objectPtr)
{
    _temporaryIdentity = objectPtr;
    _temporaryImagePath = objectPtr->getImagePath();
    _temporaryType = objectPtr->getType();
}

void SolidObject::clearTemporaryIdentity()
{
    _temporaryIdentity = nullptr;
    _temporaryImagePath = "";
    _temporaryType = "";
}
