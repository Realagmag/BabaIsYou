#pragma once

#include <iostream>

#include "../SolidObject.h"

class Skull : public SolidObject
{
public:
    Skull(std::string imagePath);
    Skull();
};