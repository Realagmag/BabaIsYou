#include "Board.h"
#include "SolidObjects/Baba.h"

Board::Board(const ObjectsOnFieldPtr3Vector &objectsOnField)
{
    _objectsOnField = objectsOnField;
    _xSize = objectsOnField.size();
    _ySize = objectsOnField[0].size();
}

Board::Board(int x, int y)
{
    _xSize = x;
    _ySize = y;

    // Resize vector for speed and memory efficiency
    // Resize x dimension
    _objectsOnField.resize(x);
    // Resize y dimension
    for (int i = 0; i < x; i++) {
        _objectsOnField[i].resize(y);
    }
    // Resize z dimension
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            _objectsOnField[i][j].resize(2);
        }
    }
}

void Board::updateState(int action)
{
    for (const Coordinates& object_coordinates : getYouObjectsCoordinates()) {
        if (action == actions::UP) {
            moveUp(object_coordinates.x, object_coordinates.y, object_coordinates.z);
        } else if (action == actions::DOWN) {
            moveDown(object_coordinates.x, object_coordinates.y, object_coordinates.z);
        } else if (action == actions::LEFT) {
            moveLeft(object_coordinates.x, object_coordinates.y, object_coordinates.z);
        } else if (action == actions::RIGHT) {
            moveRight(object_coordinates.x, object_coordinates.y, object_coordinates.z);
        }
    }
}

ObjectOnFieldPtr Board::getObject(int x, int y, int z) const
{
    return _objectsOnField[x][y][z];
}

ObjectOnFieldPtr Board::getObject(const Coordinates &coordinates) const
{
    return _objectsOnField[coordinates.x][coordinates.y][coordinates.z];
}

ObjectOnFieldPtr Board::getObject(int x, int y) const
{
    return _objectsOnField[x][y][0];
}

int Board::getXSize() const
{
    return _xSize;
}

int Board::getYSize() const
{
    return _ySize;
}

void Board::removeObject(int x, int y, int z)
{
    if (_objectsOnField[x][y][1] == nullptr ||
        (_objectsOnField[x][y][1] != nullptr && z == 1)) {
        _objectsOnField[x][y][z] = nullptr;
    }
    else if (_objectsOnField[x][y][1] != nullptr && z == 0) {
        _objectsOnField[x][y][0] = _objectsOnField[x][y][1];
        _objectsOnField[x][y][1] = nullptr;
    }
    else {
        std::cerr << "Ivalid coordinates!" << std::endl;
    }
}

void Board::addObject(int x, int y, const ObjectOnFieldPtr &object_ptr)
{
    if (_objectsOnField[x][y][0] == nullptr) {
        _objectsOnField[x][y][0] = object_ptr;
    }
    else if (_objectsOnField[x][y][0] != nullptr && _objectsOnField[x][y][1] == nullptr) {
        _objectsOnField[x][y][1] = object_ptr;
    }
    else {
        std::cerr << "3 objects cannot be in the same field!" << std::endl;
    }
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

std::vector<Coordinates> Board::getYouObjectsCoordinates() const
{
    std::vector<Coordinates> youObjectsCoordinates;

    // Iterate over vector
    for (int x = 0; x < _objectsOnField.size(); x++) {
        for (int y = 0; y < _objectsOnField[x].size(); y++) {
            for (int z = 0; z < _objectsOnField[x][y].size(); z++) {
                // Check if object has isYou flag
                if (_objectsOnField[x][y][z] != nullptr && _objectsOnField[x][y][z]->isYou) {
                        Coordinates coordinates;
                        coordinates.x = x;
                        coordinates.y = y;
                        coordinates.z = z;
                        youObjectsCoordinates.emplace_back(coordinates);
                }
            }
        }
    }

    return youObjectsCoordinates;
}