#include "Rock.h"
#include "../Parameters.h"

Rock::Rock(std::string imagePath) : SolidObject(imagePath)
{}

Rock::Rock()
{
    _imagePath = "../" + Parameters::PATHS.at("Rock");
    _nounImagePath = "../" + Parameters::PATHS.at("Rocktext");
}