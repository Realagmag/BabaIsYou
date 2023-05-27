#include "Skull.h"
#include "../Parameters.h"

Skull::Skull(std::string imagePath) : SolidObject(imagePath)
{}

Skull::Skull()
{
    _imagePath = "../" + Parameters::PATHS.at("Skull");
    _nounImagePath = "../" + Parameters::PATHS.at("Skulltext");
}