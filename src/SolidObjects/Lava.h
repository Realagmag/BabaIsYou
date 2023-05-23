#pragma once

#include <iostream>

#include "../SolidObject.h"

class Lava : public SolidObject
{
public:
    Lava(std::string imagePath);
    Lava();
};