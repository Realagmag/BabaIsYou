#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "ObjectOnField.h"

using ObjectOnFieldPtr = std::shared_ptr<ObjectOnField>;
using ObjectsOnFieldPtr3Vector = std::vector<std::vector<std::vector<ObjectOnFieldPtr>>>;

class Board
{
private:
    /* Three dimensional vector of shared pointers to the ObjectOnField class instances.
    * Third dimension is to allow two objects occupying the same field. */
    ObjectsOnFieldPtr3Vector _objectsOnField;

public:
    Board(const ObjectsOnFieldPtr3Vector &objectsOnField);
    Board();

    ObjectOnFieldPtr getObject(int x, int y, int z) const;
    ObjectOnFieldPtr getObject(int x, int y) const;

    void removeObject(int x, int y, int z);

    void addObject(int x, int y, const ObjectOnFieldPtr &object);

    void moveUp(int x, int y, int z);
    void moveDown(int x, int y, int z);
    void moveLeft(int x, int y, int z);
    void moveRight(int x, int y, int z);
};