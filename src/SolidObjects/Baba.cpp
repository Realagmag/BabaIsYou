#include "Baba.h"

Baba::Baba(std::string imagePath) : SolidObject(imagePath)
{}

std::string Baba::getImagePath(std::string direction) const
{
    if (direction == "up")
        return _imagePathUp;
    else if (direction == "down")
        return _imagePathDown;
    else if (direction == "left")
        return _imagePathLeft;
    else if (direction == "right")
        return _imagePathRight;
    // Error to handle
}

void Baba::setImagePath(std::string imagePath, std::string direction)
{
    if (direction == "up")
        _imagePathUp = imagePath;
    else if (direction == "down")
        _imagePathDown = imagePath;
    else if (direction == "left")
        _imagePathLeft = imagePath;
    else if (direction == "right")
        _imagePathRight = imagePath;
    // Error to handle
}