#pragma once

#include <iostream>
#include <string>

#include "ObjectOnField.h"

class SolidObject : public ObjectOnField
{
public:
    SolidObject(std::string imagePath);
    ~SolidObject();
};