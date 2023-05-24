#include "Flag.h"
#include "../paths.h"

Flag::Flag(std::string imagePath) : SolidObject(imagePath)
{}

Flag::Flag()
{
    _imagePath = "../" + paths.at("Flag");
    _nounImagePath = "../" + paths.at("Flagtext");
}