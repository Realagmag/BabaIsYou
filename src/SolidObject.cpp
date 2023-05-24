#include "SolidObject.h"

SolidObject::SolidObject(std::string imagePath) : ObjectOnField(imagePath)
{
    _type = "SolidObject";
}

SolidObject::SolidObject() : ObjectOnField()
{
    _type = "SolidObject";
}

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

bool SolidObject::getProperty(const std::string &property) const
{
    if (_temporaryIdentity == nullptr)
    {
        if (_properties.find(property) != _properties.end())
            return _properties.at(property);
        else
            throw std::invalid_argument("Property " + property + " does not exist.");
    }
    else
    {
        return _temporaryIdentity->getProperty(property);
    }
}

std::string SolidObject::getNounImagePath() const
{
    return _nounImagePath;
}
