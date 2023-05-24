#pragma once

#include <iostream>

#include "ObjectOnField.h"

class Property : public ObjectOnField
{
private:
    std::string _text;

public:
    Property(const std::string &imagePath, const std::string &text);
    Property(const std::string & text);

    std::string getText() const override;
};