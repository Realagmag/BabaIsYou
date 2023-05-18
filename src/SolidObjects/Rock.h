#pragma once

#include <iostream>

#include "../SolidObject.h"

class Rock : public SolidObject
{
public:
    Rock(std::string imagePath);
    Rock();
};