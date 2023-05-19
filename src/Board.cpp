#include "Board.h"

Board::Board(const ObjectOnFieldPtrs3Vector &objectOnFieldPtrs)
{
    _objectOnFieldPtrs = objectOnFieldPtrs;
    _xSize = objectOnFieldPtrs.size();
    _ySize = objectOnFieldPtrs[0].size();

    _emptyFieldPtr = std::make_shared<ObjectOnField>();

    _gameStatus = GameStatus::IN_PROGRESS;
}

Board::Board(int x, int y)
{
    _xSize = x;
    _ySize = y;

    // Make pointer to the empty field
    _emptyFieldPtr = std::make_shared<ObjectOnField>();

    // Resize vector for speed and memory efficiency
    // Resize x dimension
    _objectOnFieldPtrs.resize(x);
    // Resize y dimension
    for (int i = 0; i < x; i++) {
        _objectOnFieldPtrs[i].resize(y);
    }
    // RESEREVE 2 slots in z dimension
    // We reserve 2 slots in z dimension, because situations when more than two objects
    // are on the same field are extraordinary and then we can push back new object
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            _objectOnFieldPtrs[i][j].reserve(2);
        }
    }

    // Fill vector with empty ObjectOnFieldPtr instances
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            _objectOnFieldPtrs[i][j] = { _emptyFieldPtr};
        }
    }

    _gameStatus = GameStatus::IN_PROGRESS;
}

void Board::updateState(Action action)
{
    for (const Coordinates& object_coordinates : getYouObjectsCoordinates()) {
        switch (action)
        {
        case Action::UP:
            moveUp(object_coordinates.x, object_coordinates.y, object_coordinates.z);
            break;
        case Action::DOWN:
            moveDown(object_coordinates.x, object_coordinates.y, object_coordinates.z);
            break;
        case Action::LEFT:
            moveLeft(object_coordinates.x, object_coordinates.y, object_coordinates.z);
            break;
        case Action::RIGHT:
            moveRight(object_coordinates.x, object_coordinates.y, object_coordinates.z);
            break;
        }
    }
}

ObjectOnFieldPtr Board::getObject(int x, int y, int z) const
{
    return _objectOnFieldPtrs[x][y][z];
}

ObjectOnFieldPtr Board::getObject(const Coordinates &coordinates) const
{
    return _objectOnFieldPtrs[coordinates.x][coordinates.y][coordinates.z];
}

ObjectOnFieldPtr Board::getObject(int x, int y) const
{
    return _objectOnFieldPtrs[x][y][0];
}

ObjectOnFieldPtr Board::getemptyFieldPtr() const
{
    return _emptyFieldPtr;
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
    if (_objectOnFieldPtrs[x][y].size() == 1)
        _objectOnFieldPtrs[x][y][0] = _emptyFieldPtr;
    else
        _objectOnFieldPtrs[x][y].erase(_objectOnFieldPtrs[x][y].begin() + z);
}

void Board::addObject(int x, int y, const ObjectOnFieldPtr &ptr)
{
    if (_objectOnFieldPtrs[x][y].size() == 1 && _objectOnFieldPtrs[x][y][0] == _emptyFieldPtr)
        _objectOnFieldPtrs[x][y][0] = ptr;
    else
        _objectOnFieldPtrs[x][y].emplace_back(ptr);
}

bool Board::moveUp(int x, int y, int z)
{
    if (y < _ySize - 1){
        // Create vector from y+1 to the end of the board in up direction
        ObjectOnFieldPtrs2Vector nextObjects(_objectOnFieldPtrs[x].begin() + y + 1,
                                             _objectOnFieldPtrs[x].end());
        ObjectOnFieldPtr currentObject = _objectOnFieldPtrs[x][y][z];

        std::pair<bool, int> moveImpact = checkMoveImpact(currentObject, nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible) {
            addObject(x, y+1, currentObject);
            removeObject(x, y, z);
            for (int i = 0; i < objectsToMove; i++) {
                // Find first object that can be pushed, we know that it exists
                auto it = std::find_if(_objectOnFieldPtrs[x][y+i+1].begin(),
                                       _objectOnFieldPtrs[x][y+i+1].end(),
                                       [](const ObjectOnFieldPtr& ptr) { return ptr->isPush; });
                int index = std::distance(_objectOnFieldPtrs[x][y+i+1].begin(), it);

                addObject(x, y+i+2, _objectOnFieldPtrs[x][y+i+1][index]);
                removeObject(x, y+i+1, index);
            }
        }
    }
    else {
        return false;
    }
}

bool Board::moveDown(int x, int y, int z)
{
    addObject(x, y-1, _objectOnFieldPtrs[x][y][z]);
    removeObject(x, y, z);
    return true;
}

bool Board::moveLeft(int x, int y, int z)
{
    addObject(x-1, y, _objectOnFieldPtrs[x][y][z]);
    removeObject(x, y, z);
    return true;
}

bool Board::moveRight(int x, int y, int z)
{
    addObject(x+1, y, _objectOnFieldPtrs[x][y][z]);
    removeObject(x, y, z);
    return true;
}

std::pair<bool, int> Board::checkMoveImpact(const ObjectOnFieldPtr &currentObject,
                                            const ObjectOnFieldPtrs2Vector &nextObjects)
{
    // Check win conditions
    if (anyObjectHasTrueFlag(nextObjects[0], "isWin")) {
        _gameStatus = GameStatus::WIN;
        return std::make_pair(true, 0);
    }
    // Check lose conditions
    else if (anyObjectHasTrueFlag(nextObjects[0], "isDefeat") ||
             (currentObject->isMelt && (anyObjectHasTrueFlag(nextObjects[0], "isHot"))) ||
             anyObjectHasTrueFlag(nextObjects[0], "isSink")) {
        _gameStatus = GameStatus::LOSE;
        return std::make_pair(false, 0);
    }
    // If there is no win or lose conditions, check if move is possible
    else {
        return isMovePossible(nextObjects);
    }
}

std::pair<bool, int> Board::isMovePossible(const ObjectOnFieldPtrs2Vector &nextObjects) const
{
    bool isPushPossible = false;
    bool isMovePossible = true;
    int objectsToMove = 0;

    // Check if move is possible
    if (std::any_of(nextObjects[0].begin(), nextObjects[0].end(),
                        [&](ObjectOnFieldPtr objectOnFieldPtr) {
                            return objectOnFieldPtr->isStop && !objectOnFieldPtr->isPush; }))
    {
        isMovePossible = false;
    }

    // Check if chain of objects can be pushed
    for (std::vector<ObjectOnFieldPtr> objectOnOneFieldPtrs : nextObjects) {
        // Check if any object has isStop flag and not isPush flag
        if (std::any_of(objectOnOneFieldPtrs.begin(), objectOnOneFieldPtrs.end(),
                        [&](ObjectOnFieldPtr objectOnFieldPtr) {
                            return objectOnFieldPtr->isStop && !objectOnFieldPtr->isPush; }))
        {
            isPushPossible = false;
            break;
        }
        else if (anyObjectHasTrueFlag(objectOnOneFieldPtrs, "isPush")) {
            objectsToMove++;
            continue;
        }
        else {
            isPushPossible = true;
            break;
        }
    }

    if (!isPushPossible)
        objectsToMove = 0;

    return std::make_pair(isMovePossible, objectsToMove);
}

bool Board::anyObjectHasTrueFlag(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs,
                                 std::string flag)
{
    return std::any_of(objectOnFieldPtrs.begin(), objectOnFieldPtrs.end(), [&](ObjectOnFieldPtr ptr) {
        if (flag == "isWin")
            return ptr->isWin;
        else if (flag == "isDefeat")
            return ptr->isDefeat;
        else if (flag == "isHot")
            return ptr->isHot;
        else if (flag == "isMelt")
            return ptr->isMelt;
        else if (flag == "isSink")
            return ptr->isSink;
        else if (flag == "isPush")
            return ptr->isPush;
        else if (flag == "isStop")
            return ptr->isStop;
        else if (flag == "isYou")
            return ptr->isYou;
        else
            return false;
    });
}

std::vector<Coordinates> Board::getYouObjectsCoordinates() const
{
    std::vector<Coordinates> youObjectsCoordinates;

    // Iterate over vector
    for (int x = 0; x < _objectOnFieldPtrs.size(); x++) {
        for (int y = 0; y < _objectOnFieldPtrs[x].size(); y++) {
            for (int z = 0; z < _objectOnFieldPtrs[x][y].size(); z++) {
                // Check if object has isYou flag
                if (_objectOnFieldPtrs[x][y][z]->isYou) {
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

void Board::updateRules()
{
    // Iterate over vector
    for (int x = 0; x < _objectOnFieldPtrs.size(); x++) {
        for (int y = 0; y < _objectOnFieldPtrs[x].size(); y++) {
            if (_objectOnFieldPtrs[x][y][0]->isNoun)
        }
    }

}