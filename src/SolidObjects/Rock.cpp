#include "Rock.h"
#include "../paths.h"

Rock::Rock(std::string imagePath) : SolidObject(imagePath)
{}

Rock::Rock()
{
    _imagePath = "../" + paths.at("Rock");
}