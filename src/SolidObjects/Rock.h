#pragma once

#include <iostream>

#include "../SolidObject.h"

class Rock : public SolidObject
{
    Rock(std::string imagePath);
    Rock();
}