#include "Operator.h"

Operator::Operator(const std::string &imagePath, const std::string &text)
    : ObjectOnField(imagePath), _text(text)
{
    _type = "Operator";
    setProperty("Push", true);
    setProperty("Stop", true);

    isChangeless = true;
}

Operator::Operator(const std::string &text)
    : _text(text)
{
    _type = "Operator";
    _imagePath = "../" + Parameters::PATHS.at(text);
    setProperty("Push", true);
    setProperty("Stop", true);

    isChangeless = true;
}

std::string Operator::getText() const
{
    return _text;
}