#include "Flag.h"
#include "../Parameters.h"

Flag::Flag(std::string imagePath) : SolidObject(imagePath)
{}

Flag::Flag()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Flag");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Flagtext");
}