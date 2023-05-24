#pragma once

#include <iostream>

#include "../SolidObject.h"

class Water : public SolidObject
{
public:
    Water(std::string imagePath);
    Water();
};