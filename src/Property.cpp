#include "Property.h"

Property::Property(const std::string &imagePath, const std::string &text)
    : ObjectOnField(imagePath), _text(text)
{
    _type = "Property";
    setProperty("Push", true);
    setProperty("Stop", true);

    isChangeless = true;
}

Property::Property(const std::string &text)
    : _text(text)
{
    _type = "Property";
    _imagePath = Parameters::OBJECT_PATHS.at(text + "text");
    setProperty("Push", true);
    setProperty("Stop", true);

    isChangeless = true;
}

std::string Property::getText() const
{
    return _text;
}