#include "Lava.h"
#include "../Parameters.h"

Lava::Lava(std::string imagePath) : SolidObject(imagePath)
{}

Lava::Lava()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Lava");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Lavatext");
}