#include "SolidObject.h"

SolidObject::SolidObject(std::string imagePath) : ObjectOnField(imagePath)
{
    _type = "SolidObject";
    isChangeless = false;
}

SolidObject::SolidObject() : ObjectOnField()
{
    _type = "SolidObject";
    isChangeless = false;
}

std::shared_ptr<sf::Sprite> SolidObject::GetSpritePtr() const
{
    if (_temporaryIdentity == nullptr)
        return _spritePtr;
    else
        return _temporaryIdentity->GetSpritePtr();
}

std::string SolidObject::getImagePath() const
{
    if (_temporaryIdentity != nullptr)
        return _temporaryIdentity->getImagePath();
    return _imagePath;
}

std::string SolidObject::getType() const
{
    if (_temporaryIdentity != nullptr)
        return _temporaryIdentity->getType();
    return _type;
}

ObjectOnFieldPtr SolidObject::getTemporaryIdentity() const
{
    return _temporaryIdentity;
}

void SolidObject::setTemporaryIdentity(const ObjectOnFieldPtr &objectPtr)
{
    _temporaryIdentity = objectPtr;
}

void SolidObject::clearTemporaryIdentity()
{
    _temporaryIdentity = nullptr;
    isChangeless = false;
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
