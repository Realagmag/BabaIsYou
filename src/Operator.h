#pragma once

#include <iostream>

#include "ObjectOnField.h"

class Operator : public ObjectOnField
{
private:
    std::string _text;

public:
    Operator(const std::string &imagePath, const std::string &text);
    Operator(const std::string &text);

    std::string getText() const override;
};