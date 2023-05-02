#pragma once

class ObjectOnField
{
protected:
    std::string imagePath;

public:
    ObjectOnField(std::string imagePath);

    std::string getImagePath();
    void setImagePath(std::string imagePath);
};