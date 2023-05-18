#pragma once

#include <iostream>

#include "../SolidObject.h"

class Flag : public SolidObject
{
public:
    Flag(std::string imagePath);
    Flag();
};