#pragma once

#include <iostream>

#include "Board.h"

class Noun : public ObjectOnField
{
private:
    /* Solid Object to which the noun refers. */
    ObjectOnFieldPtr _solidObjectPtr;

public:
    Noun(std::string imagePath, ObjectOnFieldPtr solidObjectPtr);
    Noun(ObjectOnFieldPtr solidObjectPtr);

    /** Pointer to the parent object of noun. */
    ObjectOnFieldPtr getSolidObjectPtr() const override;
};