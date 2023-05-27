#include "Flag.h"
#include "../Parameters.h"

Flag::Flag(std::string imagePath) : SolidObject(imagePath)
{}

Flag::Flag()
{
    _imagePath = "../" + Parameters::PATHS.at("Flag");
    _nounImagePath = "../" + Parameters::PATHS.at("Flagtext");
}