#include "Board.h"

Board::Board(const ObjectOnFieldPtrs3Vector &objectOnFieldPtrs)
    : _objectOnFieldPtrs(objectOnFieldPtrs)
{
    _xSize = objectOnFieldPtrs.size();
    _ySize = objectOnFieldPtrs[0].size();

    _emptyFieldPtr = std::make_shared<ObjectOnField>();

    _gameStatus = GameStatus::IN_PROGRESS;
}

Board::Board(int x, int y)
    : _xSize(x), _ySize(y)
{
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
    _wereRulesChanged = false;

    // Move all "You" objects
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

    // Upadate rules if they were changed
    if (_wereRulesChanged)
    {
        updateRules();
    }

    // After move and update of rules: 1. remove duplicates on the same field,
    // 2. anihilate objects which cannot be on the same field
    // 3. check win conditions
    // for every field
    for (auto &vector2 : _objectOnFieldPtrs)
    {
        for (auto &vector1 : vector2)
        {
            mergeSameObjects(vector1);

            anihilateSomeOfObjects(vector1);

            if (checkWinConditions(vector1))
                _gameStatus = GameStatus::WIN;
        }
    }

    // Check lose condition
    if (getYouObjectsCoordinates().size() == 0)
    {
        _gameStatus = GameStatus::LOSE;
        return;
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

int Board::getZSize(int x, int y) const
{
    return _objectOnFieldPtrs[x][y].size();
}

GameStatus Board::getGameStatus() const
{
    return _gameStatus;
}

void Board::removeObject(int x, int y, int z)
{
    if (_objectOnFieldPtrs[x][y].size() == 1)
        _objectOnFieldPtrs[x][y][0] = _emptyFieldPtr;
    else
        _objectOnFieldPtrs[x][y].erase(_objectOnFieldPtrs[x][y].begin() + z);
}

void Board::removeObject(const Coordinates &coordinates)
{
    removeObject(coordinates.x, coordinates.y, coordinates.z);
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

        std::pair<bool, int> moveImpact = isMovePossible(nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            makeMove(nextObjects, currentObject, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x][y + i + 1] = std::move(nextObjects[i]);
            }

            // Remove current object from the board
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

        std::pair<bool, int> moveImpact = isMovePossible(nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            makeMove(nextObjects, currentObject, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x][y - i - 1] = std::move(nextObjects[i]);
            }

            // Remove current object from the board
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

        std::pair<bool, int> moveImpact = isMovePossible(nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            makeMove(nextObjects, currentObject, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x - 1 - i][y] = std::move(nextObjects[i]);
            }

            // Remove current object from the board
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

        std::pair<bool, int> moveImpact = isMovePossible(nextObjects);
        bool isMovePossible = moveImpact.first;
        int objectsToMove = moveImpact.second;

        if (isMovePossible)
        {
            makeMove(nextObjects, currentObject, objectsToMove);
            for (int i = 0; i <= objectsToMove; i++)
            {
                // Move semantics to avoid copying
                _objectOnFieldPtrs[x + 1 + i][y] = std::move(nextObjects[i]);
            }

            // Remove current object
            removeObject(x, y, z);

            return true;
        }
        return false;
    }
}

void Board::makeMove(ObjectOnFieldPtrs2Vector &nextObjects, ObjectOnFieldPtr &currentObject, int objectsToMove)
{
    // Move current object
    if (nextObjects[0].size() == 1 && nextObjects[0][0] == _emptyFieldPtr)
        nextObjects[0][0] = currentObject;
    else
        nextObjects[0].push_back(currentObject);

    // Move chain of objects before current object
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
            nextObjects[i][index]->getType() == "Property")
        {
            _wereRulesChanged = true;
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

std::pair<bool, int> Board::isMovePossible(const ObjectOnFieldPtrs2Vector &nextObjects) const
{
    bool isMovePossible = false;
    int objectsToMove = 0;

    // Check if move is possible
    if (std::any_of(nextObjects[0].begin(), nextObjects[0].end(),
                    [&](ObjectOnFieldPtr objectOnFieldPtr)
                    { return objectOnFieldPtr->getProperty("Stop") && !objectOnFieldPtr->getProperty("Push"); }))
    {
        isMovePossible = false;
    }

    // Check if chain of objects can be pushed
    for (const std::vector<ObjectOnFieldPtr> &objectOnOneFieldPtrs : nextObjects)
    {
        // Check if any object has isStop flag and not isPush flag
        if (std::any_of(objectOnOneFieldPtrs.begin(), objectOnOneFieldPtrs.end(),
                        [&](ObjectOnFieldPtr objectOnFieldPtr)
                        { return objectOnFieldPtr->getProperty("Stop") && !objectOnFieldPtr->getProperty("Push"); }))
        {
            isMovePossible = false;
            break;
        }
        else if (anyObjectHasProperty(objectOnOneFieldPtrs, "Push"))
        {
            objectsToMove++;
            continue;
        }
        else
        {
            isMovePossible = true;
            break;
        }
    }

    if (!isMovePossible)
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
    // Reset rules
    resetRules();

    // Load new rules
    for (int x = 0; x < _objectOnFieldPtrs.size(); x++)
    {
        for (int y = 0; y < _objectOnFieldPtrs[x].size(); y++)
        {
            // Noun, Operator and Property can only have z=0
            if (_objectOnFieldPtrs[x][y][0]->getType() == "Operator" &&
                _objectOnFieldPtrs[x][y][0]->getText() == "Is")
            {
                // Read rules from left to right
                if ((x > 0 && _objectOnFieldPtrs[x - 1][y][0]->getType() == "Noun"))
                {
                    // NOUN IS PROPERTY AND PROPERTY
                    if (x < _xSize - 1 && _objectOnFieldPtrs[x + 1][y][0]->getType() == "Property")
                    {
                        _objectOnFieldPtrs[x - 1][y][0]->getSolidObjectPtr()->setProperty(
                            _objectOnFieldPtrs[x + 1][y][0]->getText(), true);

                        // Check if AND is after first Property and second property must be added
                        if (x < _xSize - 3 && _objectOnFieldPtrs[x + 2][y][0]->getType() == "Operator" &&
                            _objectOnFieldPtrs[x + 2][y][0]->getText() == "And" &&
                            _objectOnFieldPtrs[x + 3][y][0]->getType() == "Property")
                        {
                            _objectOnFieldPtrs[x - 1][y][0]->getSolidObjectPtr()->setProperty(
                                _objectOnFieldPtrs[x + 3][y][0]->getText(), true);
                        }
                    }
                    // NOUN IS NOUN
                    else if (x < _xSize - 1 && _objectOnFieldPtrs[x + 1][y][0]->getType() == "Noun")
                    {
                        _objectOnFieldPtrs[x - 1][y][0]->getSolidObjectPtr()->setTemporaryIdentity(
                            _objectOnFieldPtrs[x + 1][y][0]->getSolidObjectPtr());
                    }
                }

                // Read rules from up to down
                if (y > 0 && _objectOnFieldPtrs[x][y - 1][0]->getType() == "Noun")
                {
                    // NOUN IS PROPERTY AND PROPERTY
                    if (y < _ySize - 1 && _objectOnFieldPtrs[x][y + 1][0]->getType() == "Property")
                    {
                        _objectOnFieldPtrs[x][y - 1][0]->getSolidObjectPtr()->setProperty(
                            _objectOnFieldPtrs[x][y + 1][0]->getText(), true);

                        // Check if AND is after first Property and second property must be added
                        if (y < _ySize - 3 && _objectOnFieldPtrs[x][y + 2][0]->getType() == "Operator" &&
                            _objectOnFieldPtrs[x][y + 2][0]->getText() == "And" &&
                            _objectOnFieldPtrs[x][y + 3][0]->getType() == "Property")
                        {
                            _objectOnFieldPtrs[x][y - 1][0]->getSolidObjectPtr()->setProperty(
                                _objectOnFieldPtrs[x][y + 3][0]->getText(), true);
                        }
                    }
                    // NOUN IS NOUN
                    else if (y < _ySize - 1 && _objectOnFieldPtrs[x][y + 1][0]->getType() == "Noun")
                    {
                        _objectOnFieldPtrs[x][y - 1][0]->getSolidObjectPtr()->setTemporaryIdentity(
                            _objectOnFieldPtrs[x][y + 1][0]->getSolidObjectPtr());
                    }
                }
            }
        }
    }
}

void Board::resetRules()
{
    // Iterate over vector
    for (const auto &vector2 : _objectOnFieldPtrs)
    {
        for (const auto &vector1 : vector2)
        {
            for (const ObjectOnFieldPtr &objectOnFieldPtr : vector1)
            {
                if (objectOnFieldPtr->getType() == "SolidObject")
                {
                    // Clear SolidObject state
                    objectOnFieldPtr->resetProperties();
                    objectOnFieldPtr->clearTemporaryIdentity();
                }
            }
        }
    }
}

void Board::mergeSameObjects(std::vector<ObjectOnFieldPtr> &vector1)
{
    if (vector1.size() > 1)
    {
        // Remove duplicates
        std::vector<ObjectOnFieldPtr>::iterator ip;
        ip = std::unique(vector1.begin(), vector1.end());
        vector1.resize(std::distance(vector1.begin(), ip));
    }
}

void Board::anihilateSomeOfObjects(std::vector<ObjectOnFieldPtr> &vector1)
{
    // Check if exist objects, which cannot be on the same field
    // (for example: Sink object and objects which is not Float), if so, make specific action
    if (vector1.size() > 1)
    {
        // Sink
        if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                        { return (objectOnFieldPtr->getProperty("Sink") && !objectOnFieldPtr->getProperty("Float")); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return !objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());

            if (vector1.size() == 0)
                vector1.emplace_back(_emptyFieldPtr);
        }
        // Defeat
        else if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                             { return (objectOnFieldPtr->getProperty("Defeat") && !objectOnFieldPtr->getProperty("Float")); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return objectOnFieldPtr->getProperty("You") && !objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());

            if (vector1.size() == 0)
                vector1.emplace_back(_emptyFieldPtr);
        }
        // Hot and Melt
        else if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                             { return objectOnFieldPtr->getProperty("Hot") && !objectOnFieldPtr->getProperty("Float"); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return objectOnFieldPtr->getProperty("Melt") && !objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());

            if (vector1.size() == 0)
                vector1.emplace_back(_emptyFieldPtr);
        }
    }
}

bool Board::checkWinConditions(std::vector<ObjectOnFieldPtr> &vector1) const
{
    if (anyObjectHasProperty(vector1, "You") && anyObjectHasProperty(vector1, "Win"))
    {
        return true;
    }
    return false;
}