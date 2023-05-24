#include "Lava.h"
#include "../paths.h"

Lava::Lava(std::string imagePath) : SolidObject(imagePath)
{}

Lava::Lava()
{
    _imagePath = "../" + paths.at("Lava");
}