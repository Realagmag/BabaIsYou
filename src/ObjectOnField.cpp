#include "ObjectOnField.h"

ObjectOnField::ObjectOnField(std::string imagePath)
: _imagePath(imagePath) {}

ObjectOnField::ObjectOnField()
{
    _imagePath = paths.at("Empty");
}

ObjectOnField::~ObjectOnField() {}

void ObjectOnField::SetSpritePtr(std::shared_ptr<sf::Sprite> new_sprite_ptr)
{
    sprite_ptr = new_sprite_ptr;
}

std::shared_ptr<sf::Sprite> ObjectOnField::GetSpritePtr()
{
    return sprite_ptr;
}


std::string ObjectOnField::getImagePath() const
{
    return _imagePath;
}

void ObjectOnField::setImagePath(std::string imagePath)
{
    _imagePath = imagePath;
}