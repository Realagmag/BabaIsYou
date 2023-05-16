#pragma once

#include <iostream>

#include "../SolidObject.h"

class Wall : public SolidObject
{
public:
    Wall(std::string imagePath);
    Wall();
};