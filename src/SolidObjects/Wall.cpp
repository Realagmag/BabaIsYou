#include "Wall.h"
#include "../Parameters.h"

Wall::Wall(std::string imagePath) : SolidObject(imagePath)
{}

Wall::Wall()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Wall");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Walltext");
}