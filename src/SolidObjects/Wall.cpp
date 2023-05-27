#include "Wall.h"
#include "../Parameters.h"

Wall::Wall(std::string imagePath) : SolidObject(imagePath)
{}

Wall::Wall()
{
    _imagePath = "../" + Parameters::PATHS.at("Wall");
    _nounImagePath = "../" + Parameters::PATHS.at("Walltext");
}