#include "ObjectOnField.h"

ObjectOnField::ObjectOnField(std::string imagePath)
: _imagePath(imagePath) {}

ObjectOnField::ObjectOnField()
{
    _imagePath = paths.at("Empty");
}

ObjectOnField::~ObjectOnField() {}

void ObjectOnField::SetTexture(sf::Texture texture)
{
    texture = texture;
}

std::shared_ptr<sf::Sprite> ObjectOnField::GetSpritePtr()
{
    return std::make_shared<sf::Sprite>(sprite);
}


std::string ObjectOnField::getImagePath() const
{
    return _imagePath;
}

void ObjectOnField::setImagePath(std::string imagePath)
{
    _imagePath = imagePath;
}