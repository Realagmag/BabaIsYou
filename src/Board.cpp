#include "Board.h"

Board::Board(const ObjectOnFieldPtrs3Vector &objectOnFieldPtrs)
    : _objectOnFieldPtrs(objectOnFieldPtrs)
{
    _xSize = objectOnFieldPtrs.size();
    _ySize = objectOnFieldPtrs[0].size();

    _emptyFieldPtr = std::make_shared<ObjectOnField>();

    _gameStatus = GameStatus::IN_PROGRESS;

    _archivalStates.reserve(Parameters::MAX_ARCHIVAL_STATES);
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

    _archivalStates.reserve(Parameters::MAX_ARCHIVAL_STATES);
}

void Board::updateState(Action action)
{
    _wereRulesChanged = false;

    // Move all "You" objects

    switch (action)
    {
    case Action::UP:
        for (const Coordinates &coordinates : getObjectsToMoveCoordinates())
        {
            moveUp(coordinates.x, coordinates.y, coordinates.z);
        }
        break;
    case Action::DOWN:
        for (const Coordinates &coordinates : getObjectsToMoveCoordinates())
        {
            moveDown(coordinates.x, coordinates.y, coordinates.z);
        }
        break;
    case Action::LEFT:
        for (const Coordinates &coordinates : getObjectsToMoveCoordinates())
        {
            moveLeft(coordinates.x, coordinates.y, coordinates.z);
        }
        break;
    case Action::RIGHT:
        for (const Coordinates &coordinates : getObjectsToMoveCoordinates())
        {
            moveRight(coordinates.x, coordinates.y, coordinates.z);
        }
        break;
    case Action::UNDO:
        undoMove();
        break;
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
    if (getObjectsToMoveCoordinates().size() == 0)
    {
        _gameStatus = GameStatus::LOSE;
        return;
    }

    // Save past board state
    if (_latestState.size() != 0 && action != Action::UNDO)
    {
        saveState(_latestState);
    }

    // Save current state as latest
    _latestState = _objectOnFieldPtrs;
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

int Board::objectWithTypeIndex(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs,
                               const std::string &type)
{
    auto it = std::find_if(objectOnFieldPtrs.begin(), objectOnFieldPtrs.end(),
                           [&](ObjectOnFieldPtr ptr)
                           { return ptr->getType() == type; });

    if (it == objectOnFieldPtrs.end())
        return -1;
    else
        return std::distance(objectOnFieldPtrs.begin(), it);
}

std::vector<Coordinates> Board::getObjectsToMoveCoordinates() const
{
    std::vector<Coordinates> objectsCoordinates;

    // Iterate over vector
    for (int x = 0; x < _objectOnFieldPtrs.size(); x++)
    {
        for (int y = 0; y < _objectOnFieldPtrs[x].size(); y++)
        {
            for (int z = 0; z < _objectOnFieldPtrs[x][y].size(); z++)
            {
                // Check if object has You property and not Stop property
                if (_objectOnFieldPtrs[x][y][z]->getProperty("You") && !_objectOnFieldPtrs[x][y][z]->getProperty("Stop"))
                {
                    Coordinates coordinates = {x, y, z};
                    objectsCoordinates.emplace_back(coordinates);
                }
            }
        }
    }

    return objectsCoordinates;
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
            int IsIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y], "Operator");

            // Noun, Operator and Property can be only on the same field
            if (IsIndex != -1 && _objectOnFieldPtrs[x][y][IsIndex]->getText() == "Is")
            {
                //  1. Read rules from left to right
                upadateRulesLeftRight(x, y);

                //  2. Read rules from up to down
                updateRulesUpDown(x, y);
            }
        }
    }
}

void Board::upadateRulesLeftRight(int x, int y)
{
    if (x > 0)
    {
        int leftNounIndex = objectWithTypeIndex(_objectOnFieldPtrs[x - 1][y], "Noun");
        if (leftNounIndex != -1)
        {
            if (x < _xSize - 1)
            {
                // NOUN IS PROPERTY
                int rightPropertyIndex = objectWithTypeIndex(_objectOnFieldPtrs[x + 1][y], "Property");
                int rightNounIndex = objectWithTypeIndex(_objectOnFieldPtrs[x + 1][y], "Noun");
                if (rightPropertyIndex != -1)
                {
                    _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->setProperty(
                        _objectOnFieldPtrs[x + 1][y][rightPropertyIndex]->getText(), true);
                }
                // NOUN IS NOUN
                else if (rightNounIndex != -1 &&
                         !_objectOnFieldPtrs[x + 1][y][rightNounIndex]->getSolidObjectPtr()->isChangeless)
                {
                    if (_objectOnFieldPtrs[x - 1][y][leftNounIndex] == _objectOnFieldPtrs[x + 1][y][rightNounIndex])
                    {
                        _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->clearTemporaryIdentity();
                        _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->isChangeless = true;
                    }
                    else
                    {
                        _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->setTemporaryIdentity(
                            _objectOnFieldPtrs[x + 1][y][rightNounIndex]->getSolidObjectPtr());
                    }
                }

                // AND
                if (x < _xSize - 3)
                {
                    int AndIndex = objectWithTypeIndex(_objectOnFieldPtrs[x + 2][y], "Operator");
                    if (AndIndex != -1 && (rightNounIndex != -1 || rightPropertyIndex != -1) &&
                        _objectOnFieldPtrs[x + 2][y][AndIndex]->getText() == "And")
                    {
                        // AND PROPERTY
                        int rightAndPropertyIndex = objectWithTypeIndex(_objectOnFieldPtrs[x + 3][y], "Property");
                        int rightAndNounIndex = objectWithTypeIndex(_objectOnFieldPtrs[x + 3][y], "Noun");
                        if (rightAndPropertyIndex != -1)
                        {
                            _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->setProperty(
                                _objectOnFieldPtrs[x + 3][y][rightAndPropertyIndex]->getText(), true);
                        }
                        // AND NOUN
                        else if (rightNounIndex == -1 && rightAndNounIndex != -1 &&
                                 !_objectOnFieldPtrs[x - 1][y][rightAndNounIndex]->getSolidObjectPtr()->isChangeless)
                        {
                            if (_objectOnFieldPtrs[x - 1][y][leftNounIndex] == _objectOnFieldPtrs[x + 3][y][rightAndNounIndex])
                            {
                                _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->clearTemporaryIdentity();
                                _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->isChangeless = true;
                            }
                            else
                            {
                                _objectOnFieldPtrs[x - 1][y][leftNounIndex]->getSolidObjectPtr()->setTemporaryIdentity(
                                    _objectOnFieldPtrs[x + 3][y][rightAndNounIndex]->getSolidObjectPtr());
                            }
                        }
                    }
                }
            }
        }
    }
}

void Board::updateRulesUpDown(int x, int y)
{
    if (y > 0)
    {
        int upNounIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y - 1], "Noun");
        if (upNounIndex != -1)
        {
            // NOUN IS PROPERTY
            if (y < _ySize - 1)
            {
                int downPropertyIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y + 1], "Property");
                int downNounIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y + 1], "Noun");
                if (downPropertyIndex != -1)
                {
                    _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->setProperty(
                        _objectOnFieldPtrs[x][y + 1][downPropertyIndex]->getText(), true);
                }
                // NOUN IS NOUN
                else if (downNounIndex != -1 &&
                         !_objectOnFieldPtrs[x][y + 1][downNounIndex]->getSolidObjectPtr()->isChangeless)
                {
                    if (_objectOnFieldPtrs[x][y - 1][upNounIndex] == _objectOnFieldPtrs[x][y + 1][downNounIndex])
                    {
                        _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->clearTemporaryIdentity();
                        _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->isChangeless = true;
                    }
                    else
                    {
                        _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->setTemporaryIdentity(
                            _objectOnFieldPtrs[x][y + 1][downNounIndex]->getSolidObjectPtr());
                    }
                }

                // AND
                if (y < _ySize - 3)
                {
                    int AndIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y + 2], "Operator");
                    if (AndIndex != -1 && (downNounIndex != -1 || downPropertyIndex != -1) &&
                        _objectOnFieldPtrs[x][y + 2][AndIndex]->getText() == "And")
                    {
                        // AND PROPERTY
                        int downAndPropertyIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y + 3], "Property");
                        int downAndNounIndex = objectWithTypeIndex(_objectOnFieldPtrs[x][y + 3], "Noun");
                        if (downAndPropertyIndex != -1)
                        {
                            _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->setProperty(
                                _objectOnFieldPtrs[x][y + 3][downAndPropertyIndex]->getText(), true);
                        }
                        // AND NOUN
                        else if (downNounIndex == -1 && downAndNounIndex != -1 &&
                                 !_objectOnFieldPtrs[x][y + 3][downAndNounIndex]->getSolidObjectPtr()->isChangeless)
                        {
                            if (_objectOnFieldPtrs[x][y - 1][upNounIndex] == _objectOnFieldPtrs[x][y + 3][downAndNounIndex])
                            {
                                _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->clearTemporaryIdentity();
                                _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->isChangeless = true;
                            }
                            else
                            {
                                _objectOnFieldPtrs[x][y - 1][upNounIndex]->getSolidObjectPtr()->setTemporaryIdentity(
                                    _objectOnFieldPtrs[x][y + 3][downAndNounIndex]->getSolidObjectPtr());
                            }
                        }
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
    if (vector1.size() > 1)
    {
        // Sink
        // If sink object is not float
        if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                        { return (objectOnFieldPtr->getProperty("Sink") && !objectOnFieldPtr->getProperty("Float")); }))
        {
            // Count objects which are not Float in the vector
            int countNotFloat = std::count_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                              { return !objectOnFieldPtr->getProperty("Float"); });

            // Assert that there is more than one object which is not Float (more than this Sink object)
            if (countNotFloat > 1)
            {
                vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                             { return !objectOnFieldPtr->getProperty("Float"); }),
                              vector1.end());
            }
        }
        // If sink object is float
        else if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                             { return (objectOnFieldPtr->getProperty("Sink") && objectOnFieldPtr->getProperty("Float")); }))
        {
            // Count objects which are Float in the vector
            int countFloat = std::count_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                           { return objectOnFieldPtr->getProperty("Float"); });

            // Assert that there is more than one object which is Float (more than this Sink object)
            if (countFloat > 1)
            {
                vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                             { return objectOnFieldPtr->getProperty("Float"); }),
                              vector1.end());
            }
        }

        // Defeat
        if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                        { return (objectOnFieldPtr->getProperty("Defeat") && !objectOnFieldPtr->getProperty("Float")); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return objectOnFieldPtr->getProperty("You") && !objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());
        }
        else if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                             { return (objectOnFieldPtr->getProperty("Defeat") && objectOnFieldPtr->getProperty("Float")); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return objectOnFieldPtr->getProperty("You") && objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());
        }

        // Hot and Melt
        if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                        { return objectOnFieldPtr->getProperty("Hot") && !objectOnFieldPtr->getProperty("Float"); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return objectOnFieldPtr->getProperty("Melt") && !objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());
        }
        else if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                             { return objectOnFieldPtr->getProperty("Hot") && objectOnFieldPtr->getProperty("Float"); }))
        {
            vector1.erase(std::remove_if(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                                         { return objectOnFieldPtr->getProperty("Melt") && objectOnFieldPtr->getProperty("Float"); }),
                          vector1.end());
        }
    }

    if (vector1.size() == 0)
        vector1.emplace_back(_emptyFieldPtr);
}

bool Board::checkWinConditions(const std::vector<ObjectOnFieldPtr> &vector1) const
{
    if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                    { return objectOnFieldPtr->getProperty("You") && !objectOnFieldPtr->getProperty("Float"); }) &&
        std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                    { return objectOnFieldPtr->getProperty("Win") && !objectOnFieldPtr->getProperty("Float"); }))
    {
        return true;
    }
    else if (std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                         { return objectOnFieldPtr->getProperty("You") && objectOnFieldPtr->getProperty("Float"); }) &&
             std::any_of(vector1.begin(), vector1.end(), [](const ObjectOnFieldPtr &objectOnFieldPtr)
                         { return objectOnFieldPtr->getProperty("Win") && objectOnFieldPtr->getProperty("Float"); }))
    {
        return true;
    }
    return false;
}

void Board::saveState(const ObjectOnFieldPtrs3Vector &state)
{
    if (_archivalStates.size() < Parameters::MAX_ARCHIVAL_STATES)
    {
        _archivalStates.push_back(state);
    }
    else
    {
        _archivalStates.erase(_archivalStates.begin());
        _archivalStates.push_back(state);
    }
}

void Board::undoMove()
{
    if (_archivalStates.size() > 0)
    {
        _objectOnFieldPtrs = _archivalStates[_archivalStates.size() - 1];
        _archivalStates.pop_back();

        // Update rules, because board state has changed
        updateRules();
    }
}