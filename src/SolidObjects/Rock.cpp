#include "Rock.h"
#include "../Parameters.h"

Rock::Rock(std::string imagePath) : SolidObject(imagePath)
{}

Rock::Rock()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Rock");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Rocktext");
}