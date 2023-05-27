#include "ObjectOnField.h"
#include <string>

ObjectOnField::ObjectOnField(std::string imagePath)
    : _imagePath(imagePath), _type("Empty") {}

ObjectOnField::ObjectOnField()
    : _imagePath(Parameters::PATHS.at("Empty")), _type("Empty") {}

ObjectOnField::~ObjectOnField() {}

void ObjectOnField::SetSpritePtr(std::shared_ptr<sf::Sprite> newSpritePtr)
{
    _spritePtr = newSpritePtr;
}

std::shared_ptr<sf::Sprite> ObjectOnField::GetSpritePtr() const
{
    return _spritePtr;
}

std::string ObjectOnField::getImagePath() const
{
    return _imagePath;
}

std::string ObjectOnField::getType() const
{
    return _type;
}

ObjectOnFieldPtr ObjectOnField::getTemporaryIdentity() const
{
    return nullptr;
}

void ObjectOnField::setTemporaryIdentity(const ObjectOnFieldPtr &objectPtr)
{
    return;
}

void ObjectOnField::clearTemporaryIdentity()
{
    return;
}

std::shared_ptr<ObjectOnField> ObjectOnField::getSolidObjectPtr() const
{
    return nullptr;
}

void ObjectOnField::resetProperties()
{
    for (auto &property : _properties)
        property.second = false;
}

bool ObjectOnField::getProperty(const std::string &property) const
{
    // Check if property exists and if so, return its value
    if (_properties.find(property) != _properties.end())
        return _properties.at(property);
    else
        throw std::invalid_argument("Property " + property + " does not exist.");
}

void ObjectOnField::setProperty(const std::string &property, bool value)
{
    // Check if property exists and if so, set it to value
    if (_properties.find(property) != _properties.end())
        _properties[property] = value;
    else
        throw std::invalid_argument("Property " + property + " does not exist.");
}

std::string ObjectOnField::getNounImagePath() const
{
    return "";
}

std::string ObjectOnField::getText() const
{
    return "";
}