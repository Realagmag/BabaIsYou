#include "Baba.h"

Baba::Baba(std::string imagePath) : SolidObject(imagePath)
{
    isYou = false;
    isWin = false;
    isPush = false;
    isStop = false;
    isSink = false;
    isHot = false;
    isMelt = false;
    isDefeat = false;
}
