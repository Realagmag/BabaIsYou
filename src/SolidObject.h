#pragma once

#include <iostream>
#include <string>

#include "ObjectOnField.h"

class SolidObject : public ObjectOnField
{
private:
    /* Image path, when SOLID_OBJECT IS ANOTHER_SOLID_OBJECT. */
    std::string _temporaryImagePath;

public:
    SolidObject(std::string imagePath);
    SolidObject();

    std::string getImagePath() const override;
    void setImagePath(std::string imagePath) override;

    void clearTemporaryImagePath();
};