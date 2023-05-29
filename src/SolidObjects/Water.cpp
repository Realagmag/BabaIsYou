#include "Water.h"
#include "../Parameters.h"

Water::Water(std::string imagePath) : SolidObject(imagePath)
{}

Water::Water()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Water");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Watertext");
}