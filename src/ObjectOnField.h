#pragma once

#include <iostream>
#include "paths.h"

class ObjectOnField
{
protected:
    std::string _imagePath;

public:
    ObjectOnField(std::string imagePath);
    ObjectOnField();
    virtual ~ObjectOnField();

    virtual std::string getImagePath() const;
    virtual void setImagePath(std::string imagePath);

    bool isSolidObject = false;
    bool isNoun = false;
    bool isOperator = false;
    bool isKeyword = false;

    bool isYou = false;
    bool isWin = false;
    bool isStop = false;
    bool isPush = false;
    bool isSink = false;
    bool isDefeat = false;
    bool isHot = false;
    bool isMelt = false;
};