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
    for (int i = 0; i < x; i++)
    {
        _objectOnFieldPtrs[i].resize(y);
    }
    // RESEREVE 2 slots in z dimension
    // We reserve 2 slots in z dimension, because situations when more than two objects
    // are on the same field are extraordinary and then we can push back new object
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            _objectOnFieldPtrs[i][j].reserve(2);
        }
    }

    // Fill vector with empty ObjectOnFieldPtr instances
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            _objectOnFieldPtrs[i][j] = {_emptyFieldPtr};
        }
    }

    _gameStatus = GameStatus::IN_PROGRESS;
}

void Board::updateState(Action action)
{
    _wasRulesChanged = false;

    for (const Coordinates &object_coordinates : getYouObjectsCoordinates())
    {
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

    if (_wasRulesChanged)
    {
        updateRules();
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
        _objectOnFieldPtrs[x][y].push_back(ptr);
}

bool Board::moveDown(int x, int y, int z)
{
    if (y < _ySize - 1)
    {
        ObjectOnFieldPtrs2Vector nextObjects(_objectOnFieldPtrs[x].begin() + y + 1,
                                             _objectOnFieldPtrs[x].end());
        ObjectOnFieldPtr currentObject = _objectOnFieldPtrs[x][y][z];

        std::pair<bool, int> moveImpact = checkMoveImpact(currentObject, nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            // Move chain of objects before current object
            makeMove(nextObjects, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x][y + i + 1] = std::move(nextObjects[i]);
            }

            // Move current object
            addObject(x, y + 1, currentObject);
            removeObject(x, y, z);

            return true;
        }
        return false;
    }
    return false;
}

bool Board::moveUp(int x, int y, int z)
{
    if (y > 0)
    {
        ObjectOnFieldPtrs2Vector nextObjects(std::make_reverse_iterator(_objectOnFieldPtrs[x].begin() + y),
                                             std::make_reverse_iterator(_objectOnFieldPtrs[x].begin()));
        ObjectOnFieldPtr currentObject = _objectOnFieldPtrs[x][y][z];

        std::pair<bool, int> moveImpact = checkMoveImpact(currentObject, nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            // Move chain of objects before current object
            if (objectsToMove > 0)
            {
                makeMove(nextObjects, objectsToMove);
                for (int i = 0; i <= objectsToMove; i++)
                {
                    // Move semantics to avoid copying
                    _objectOnFieldPtrs[x][y - i - 1] = std::move(nextObjects[i]);
                }
            }

            // Move current object
            addObject(x, y - 1, currentObject);
            removeObject(x, y, z);

            return true;
        }
        return false;
    }
}

bool Board::moveLeft(int x, int y, int z)
{
    if (x > 0)
    {
        ObjectOnFieldPtrs2Vector nextObjects;
        nextObjects.resize(x);
        for (int i = x - 1; i >= 0; i--)
        {
            nextObjects[x - 1 - i] = _objectOnFieldPtrs[i][y];
        }
        ObjectOnFieldPtr currentObject = _objectOnFieldPtrs[x][y][z];

        std::pair<bool, int> moveImpact = checkMoveImpact(currentObject, nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            // Move chain of objects before current object
            makeMove(nextObjects, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x - 1 - i][y] = std::move(nextObjects[i]);
            }

            // Move current object
            addObject(x - 1, y, currentObject);
            removeObject(x, y, z);

            return true;
        }
        return false;
    }
}

bool Board::moveRight(int x, int y, int z)
{
    if (x < _xSize - 1)
    {
        ObjectOnFieldPtrs2Vector nextObjects;
        nextObjects.resize(_xSize - x - 1);
        for (int i = x + 1; i < _xSize; i++)
        {
            nextObjects[i - x - 1] = _objectOnFieldPtrs[i][y];
        }
        ObjectOnFieldPtr currentObject = _objectOnFieldPtrs[x][y][z];

        std::pair<bool, int> moveImpact = checkMoveImpact(currentObject, nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            // Move chain of objects before current object
            makeMove(nextObjects, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x + 1 + i][y] = std::move(nextObjects[i]);
            }

            // Move current object
            addObject(x + 1, y, currentObject);
            removeObject(x, y, z);

            return true;
        }
        return false;
    }
}

void Board::makeMove(ObjectOnFieldPtrs2Vector &nextObjects, int objectsToMove)
{
    for (int i = 0; i < objectsToMove; i++)
    {
        // Find first object that can be pushed, we know that it exists
        auto it = std::find_if(nextObjects[i].begin(), nextObjects[i].end(),
                               [](const ObjectOnFieldPtr &ptr)
                               { return ptr->getProperty("Push"); });
        int index = std::distance(nextObjects[i].begin(), it);

        // Check if this move will change rules
        if (nextObjects[i][index]->getType() == "Noun" ||
            nextObjects[i][index]->getType() == "Operator" ||
            nextObjects[i][index]->getType() == "Attribute")
        {
            _wasRulesChanged = true;
        }

        // Add object to the next field
        if (nextObjects[i + 1].size() == 1 && nextObjects[i + 1][0] == _emptyFieldPtr)
            nextObjects[i + 1][0] = nextObjects[i][index];
        else
            nextObjects[i + 1].push_back(nextObjects[i][index]);

        // Remove object from the current field
        if (nextObjects[i].size() == 1)
            nextObjects[i][0] = _emptyFieldPtr;
        else
            nextObjects[i].erase(nextObjects[i].begin() + index);
    }
}

std::pair<bool, int> Board::checkMoveImpact(const ObjectOnFieldPtr &currentObject,
                                            const ObjectOnFieldPtrs2Vector &nextObjects)
{
    // Check win conditions
    if (anyObjectHasProperty(nextObjects[0], "Win"))
    {
        _gameStatus = GameStatus::WIN;
        return std::make_pair(true, 0);
    }
    // Check lose conditions
    else if (anyObjectHasProperty(nextObjects[0], "Defeat") ||
             (currentObject->getProperty("Melt") && (anyObjectHasProperty(nextObjects[0], "Hot"))) ||
             anyObjectHasProperty(nextObjects[0], "Sink"))
    {
        _gameStatus = GameStatus::LOSE;
        return std::make_pair(false, 0);
    }
    // If there is no win or lose conditions, check if move is possible
    else
    {
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
                    [&](ObjectOnFieldPtr objectOnFieldPtr)
                    { return objectOnFieldPtr->getProperty("Stop") && !objectOnFieldPtr->getProperty("Push"); }))
    {
        isMovePossible = false;
    }

    // Check if chain of objects can be pushed
    for (std::vector<ObjectOnFieldPtr> objectOnOneFieldPtrs : nextObjects)
    {
        // Check if any object has isStop flag and not isPush flag
        if (std::any_of(objectOnOneFieldPtrs.begin(), objectOnOneFieldPtrs.end(),
                        [&](ObjectOnFieldPtr objectOnFieldPtr)
                        { return objectOnFieldPtr->getProperty("Stop") && !objectOnFieldPtr->getProperty("Push"); }))
        {
            isPushPossible = false;
            break;
        }
        else if (anyObjectHasProperty(objectOnOneFieldPtrs, "Push"))
        {
            objectsToMove++;
            continue;
        }
        else
        {
            isPushPossible = true;
            break;
        }
    }

    if (!isPushPossible)
        objectsToMove = 0;

    return std::make_pair(isMovePossible, objectsToMove);
}

bool Board::anyObjectHasProperty(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs,
                                 const std::string &property)
{
    return std::any_of(objectOnFieldPtrs.begin(), objectOnFieldPtrs.end(), [&](ObjectOnFieldPtr ptr)
                       { return ptr->getProperty(property); });
}

std::vector<Coordinates> Board::getYouObjectsCoordinates() const
{
    std::vector<Coordinates> youObjectsCoordinates;

    // Iterate over vector
    for (int x = 0; x < _objectOnFieldPtrs.size(); x++)
    {
        for (int y = 0; y < _objectOnFieldPtrs[x].size(); y++)
        {
            for (int z = 0; z < _objectOnFieldPtrs[x][y].size(); z++)
            {
                // Check if object has You property
                if (_objectOnFieldPtrs[x][y][z]->getProperty("You"))
                {
                    Coordinates coordinates = {x, y, z};
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
    for (int x = 0; x < _objectOnFieldPtrs.size(); x++)
    {
        for (int y = 0; y < _objectOnFieldPtrs[x].size(); y++)
        {
            // Noun, Operator and Property can only have z=0
            if (_objectOnFieldPtrs[x][y][0]->getType() == "Operator")
            {
                // Clear parent SolidObject
                _objectOnFieldPtrs[x][y][0]->getSolidObjectPtr()->clearTemporaryIdentity();
                _objectOnFieldPtrs[x][y][0]->getSolidObjectPtr()->resetProperties();

            }
        }
    }
}
