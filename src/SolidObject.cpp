#include "SolidObject.h"

SolidObject::SolidObject(std::string imagePath) : ObjectOnField(imagePath)
{
    isSolidObject = true;
}