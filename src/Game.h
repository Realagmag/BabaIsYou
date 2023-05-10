#pragma once

#include <iostream>

#include "Board.h"

class Game
{
private:
    Board _board;

public:
    Game(const Board &board);
};