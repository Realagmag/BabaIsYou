#include "Baba.h"
#include "../Parameters.h"

Baba::Baba(std::string imagePath) : SolidObject(imagePath)
{}

Baba::Baba()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Baba");
    _imagePathUp = Parameters::OBJECT_PATHS.at("BabaUp");
    _imagePathDown = Parameters::OBJECT_PATHS.at("BabaDown");
    _imagePathLeft = Parameters::OBJECT_PATHS.at("BabaLeft");
    _imagePathRight = Parameters::OBJECT_PATHS.at("BabaRight");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Babatext");
}

std::string Baba::getImagePath() const
{
    return _imagePath;
}

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
    else
        throw InvalidDirectionException(direction);
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
    else
        throw InvalidDirectionException(direction);
}