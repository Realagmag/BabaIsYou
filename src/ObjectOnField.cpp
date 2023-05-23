#include "ObjectOnField.h"

ObjectOnField::ObjectOnField(std::string imagePath)
    : _imagePath(imagePath), _type("Empty") {}

ObjectOnField::ObjectOnField()
    : _imagePath(paths.at("Empty")), _type("Empty") {}

ObjectOnField::~ObjectOnField() {}

void ObjectOnField::SetSpritePtr(std::shared_ptr<sf::Sprite> new_sprite_ptr)
{
    _sprite_ptr = new_sprite_ptr;
}

std::shared_ptr<sf::Sprite> ObjectOnField::GetSpritePtr()
{
    return _sprite_ptr;
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