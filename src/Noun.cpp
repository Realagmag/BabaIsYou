#include "Noun.h"

Noun::Noun(std::string imagePath, std::shared_ptr<SolidObject> solidObjectPtr)
    : ObjectOnField(imagePath), _solidObjectPtr(solidObjectPtr)
{
    _type = "Noun";
    setProperty("Push", true);
    setProperty("Stop", true);
}

ObjectOnFieldPtr Noun::getSolidObjectPtr() const
{
    return _solidObjectPtr;
}