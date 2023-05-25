#include "Water.h"
#include "../paths.h"

Water::Water(std::string imagePath) : SolidObject(imagePath)
{}

Water::Water()
{
    _imagePath = "../" + paths.at("Water");
    _nounImagePath = "../" + paths.at("Watertext");
}