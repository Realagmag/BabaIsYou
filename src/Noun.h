#pragma once

#include <iostream>

#include "Board.h"

class Noun
{
private:
    std::string _imagePath;

    /* Solid Object to which the noun refers. */
    ObjectOnFieldPtr _solidObjectPtr;
};