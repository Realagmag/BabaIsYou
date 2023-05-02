#include "Game.h"

Game::Game(const Board &board)
: _board(board) {}

Board Game::getBoard() const
{
    return _board;
}
