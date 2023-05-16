#include "Wall.h"
#include "../paths.h"

Wall::Wall(std::string imagePath) : SolidObject(imagePath)
{}

Wall::Wall()
{
    _imagePath = "../" + paths.at("Wall");
}