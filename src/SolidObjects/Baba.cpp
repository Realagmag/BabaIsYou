#include "Baba.h"
#include "../paths.h"

Baba::Baba(std::string imagePath) : SolidObject(imagePath)
{}

Baba::Baba()
{
    _imagePath = "../" + paths.at("Baba");
    _imagePathUp = "../" + paths.at("BabaUp");
    _imagePathDown = "../" + paths.at("BabaDown");
    _imagePathLeft = "../" + paths.at("BabaLeft");
    _imagePathRight = "../" + paths.at("BabaRight");
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