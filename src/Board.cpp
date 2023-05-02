#include "Board.h"

Board::Board(const ObjectsOnFieldPtr3Vector &objectsOnField)
{
    _objectsOnField = objectsOnField;
}

Board::Board() {}

ObjectOnFieldPtr Board::getObject(int x, int y, int z) const
{
    return _objectsOnField[x][y][z];
}

ObjectOnFieldPtr Board::getObject(int x, int y) const
{
    return _objectsOnField[x][y][0];
}

void Board::removeObject(int x, int y, int z)
{
    if (_objectsOnField[x][y].size() == 1) {
        _objectsOnField[x][y][0] = nullptr;
    }
    else {
        _objectsOnField[x][y].erase(_objectsOnField[x][y].begin() + z);
    }
}

void Board::addObject(int x, int y, const ObjectOnFieldPtr &object)
{
    _objectsOnField[x][y].emplace_back(object);
}

void Board::moveUp(int x, int y, int z)
{
    addObject(x, y+1, _objectsOnField[x][y][z]);
    removeObject(x, y, z);
}

void Board::moveDown(int x, int y, int z)
{
    addObject(x, y-1, _objectsOnField[x][y][z]);
    removeObject(x, y, z);
}

void Board::moveLeft(int x, int y, int z)
{
    addObject(x-1, y, _objectsOnField[x][y][z]);
    removeObject(x, y, z);
}

void Board::moveRight(int x, int y, int z)
{
    addObject(x+1, y, _objectsOnField[x][y][z]);
    removeObject(x, y, z);
}
