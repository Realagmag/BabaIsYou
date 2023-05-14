#include "SolidObject.h"

SolidObject::SolidObject(std::string imagePath) : ObjectOnField(imagePath)
{
    isSolidObject = true;
    _temporaryImagePath = "";
}

SolidObject::SolidObject()
{
    isSolidObject = true;
    _temporaryImagePath = "";
}

std::string SolidObject::getImagePath() const
{
    if (_temporaryImagePath != "")
        return _temporaryImagePath;
    return _imagePath;
}

void SolidObject::setImagePath(std::string imagePath)
{
    _temporaryImagePath = imagePath;
}

void SolidObject::clearTemporaryImagePath()
{
    _temporaryImagePath = "";
}