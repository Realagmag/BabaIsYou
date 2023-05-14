#pragma once

#include <iostream>

#include "../SolidObject.h"

class Baba : public SolidObject
{
private:
    std::string _imagePathUp, _imagePathDown, _imagePathLeft, _imagePathRight;

public:
    Baba(std::string imagePath);
    Baba();

    std::string getImagePath() const override;
    std::string getImagePath(std::string direction) const;

    void setImagePath(std::string imagePath, std::string direction);
};