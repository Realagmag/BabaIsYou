#include "Skull.h"
#include "../Parameters.h"

Skull::Skull(std::string imagePath) : SolidObject(imagePath)
{}

Skull::Skull()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Skull");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Skulltext");
}