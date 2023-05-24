#pragma once

#include <iostream>

#include "Board.h"

class Noun : public ObjectOnField
{
private:
    /* Solid Object to which the noun refers. */
    std::shared_ptr<SolidObject> _solidObjectPtr;

public:
    Noun(std::string imagePath, std::shared_ptr<SolidObject> solidObjectPtr);

    /** Pointer to the parent object of noun. */
    ObjectOnFieldPtr getSolidObjectPtr() const override;
};