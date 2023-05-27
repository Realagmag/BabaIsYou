#include "Noun.h"

Noun::Noun(std::string imagePath, ObjectOnFieldPtr solidObjectPtr)
    : ObjectOnField(imagePath), _solidObjectPtr(solidObjectPtr)
{
    _type = "Noun";
    setProperty("Push", true);
    setProperty("Stop", true);

    isChangeless = true;
}

Noun::Noun(ObjectOnFieldPtr solidObjectPtr)
    : _solidObjectPtr(solidObjectPtr)
{
    _type = "Noun";
    _imagePath = _solidObjectPtr->getNounImagePath();
    setProperty("Push", true);
    setProperty("Stop", true);

    isChangeless = true;
}

ObjectOnFieldPtr Noun::getSolidObjectPtr() const
{
    return _solidObjectPtr;
}