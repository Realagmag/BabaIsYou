#include "Lava.h"
#include "../Parameters.h"

Lava::Lava(std::string imagePath) : SolidObject(imagePath)
{}

Lava::Lava()
{
    _imagePath = "../" + Parameters::PATHS.at("Lava");
    _nounImagePath = "../" + Parameters::PATHS.at("Lavatext");
}