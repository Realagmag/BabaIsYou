#pragma once

#include <iostream>

#include "SolidObject.h"

class Baba : public SolidObject
{
public:
    Baba(std::string imagePath);

    static bool isYou;
    static bool isWin;
    static bool isPush;
    static bool isStop;
    static bool isSink;
    static bool isHot;
    static bool isMelt;
    static bool isDefeat;
};