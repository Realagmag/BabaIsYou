#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "ObjectOnField.h"
#include "SolidObject.h"

using ObjectOnFieldPtr = std::shared_ptr<ObjectOnField>;
using ObjectsOnFieldPtr3Vector = std::vector<std::vector<std::vector<ObjectOnFieldPtr>>>;

enum actions { UP, DOWN, LEFT, RIGHT };

struct Coordinates
{
    int x;
    int y;
    int z;
};

class Board
{
private:
    /** Three dimensional vector of shared pointers to the ObjectOnField class instances.
    * Third dimension is to allow two objects occupying the same field. */
    ObjectsOnFieldPtr3Vector _objectsOnField;

    /** Size of board */
    int _xSize, _ySize;

public:
    Board(const ObjectsOnFieldPtr3Vector &objectsOnField);

    /** @param x First dimension size.
     * @param y Second dimension size.
     * Third dimension size is set to 2.  */
    Board(int x, int y);

    /** Function which takes user action and do everything to update board state
    * properly after that action.
    * @param action Integer from actions enum. */
    void updateState(int action);

    /** Getters */
    ObjectOnFieldPtr getObject(int x, int y, int z) const;
    ObjectOnFieldPtr getObject(const Coordinates &coordinates) const;
    ObjectOnFieldPtr getObject(int x, int y) const;
    int getXSize() const;
    int getYSize() const;

    /** Remove object - replace it nullptr*/
    void removeObject(int x, int y, int z);

    /** Add object to board */
    void addObject(int x, int y, const ObjectOnFieldPtr &object);

    /** Check if move is possible and move if it is possible. */
    void moveUp(int x, int y, int z);
    void moveDown(int x, int y, int z);
    void moveLeft(int x, int y, int z);
    void moveRight(int x, int y, int z);

    /** Finds solid objects which have isYou flag set to true from objects on board
     * and returns their coordinates. */
    std::vector<Coordinates> getYouObjectsCoordinates() const;
};