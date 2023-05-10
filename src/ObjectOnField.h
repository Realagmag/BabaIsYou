#pragma once

#include <iostream>

class ObjectOnField
{
protected:
    std::string _imagePath;

public:
    ObjectOnField(std::string imagePath);
    ObjectOnField();
    ~ObjectOnField();

    std::string getImagePath() const;
    void setImagePath(std::string imagePath);

    bool isSolidObject = false;
    bool isObjectWord = false;
    bool isOperator = false;
    bool isKeyword = false;

    bool isYou = false;
    bool isWin = false;
    bool isStop = false;
    bool isPush = false;
    bool isSink = false;
    bool isDefeat = false;
    bool isHot = false;
};