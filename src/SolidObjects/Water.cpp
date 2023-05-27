#include "Water.h"
#include "../Parameters.h"

Water::Water(std::string imagePath) : SolidObject(imagePath)
{}

Water::Water()
{
    _imagePath = "../" + Parameters::PATHS.at("Water");
    _nounImagePath = "../" + Parameters::PATHS.at("Watertext");
}