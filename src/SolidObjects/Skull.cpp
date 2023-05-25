#include "Skull.h"
#include "../paths.h"

Skull::Skull(std::string imagePath) : SolidObject(imagePath)
{}

Skull::Skull()
{
    _imagePath = "../" + paths.at("Skull");
    _nounImagePath = "../" + paths.at("Skulltext");
}