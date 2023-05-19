#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>

#include "ObjectOnField.h"
#include "SolidObject.h"

using ObjectOnFieldPtr = std::shared_ptr<ObjectOnField>;
using ObjectOnFieldPtrs2Vector = std::vector<std::vector<ObjectOnFieldPtr>>;
using ObjectOnFieldPtrs3Vector = std::vector<std::vector<std::vector<ObjectOnFieldPtr>>>;

enum Action { UP, DOWN, LEFT, RIGHT, WAIT };

enum GameStatus
{
    IN_PROGRESS,
    WIN,
    LOSE,
    FROZEN // There is no isYou object on board
};

/*Struct to store coordinates of object on board*/
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
    ObjectOnFieldPtrs3Vector _objectOnFieldPtrs;

    /** Size of board */
    int _xSize, _ySize;

    /** Status of the game */
    GameStatus _gameStatus;

    /** Ptr to the empty field */
    ObjectOnFieldPtr _emptyFieldPtr;

public:
    Board(const ObjectOnFieldPtrs3Vector &objectsOnFieldPtrs);

    /** @param x First dimension size.
     * @param y Second dimension size.
     * Third dimension size is set to 2.  */
    Board(int x, int y);

    /** Function which takes user action and do everything to update board state
    * properly after that action.
    * @param action Integer from actions enum. */
    void updateState(Action action);

    /** Getters */
    ObjectOnFieldPtr getObject(int x, int y, int z) const;

    ObjectOnFieldPtr getObject(const Coordinates &coordinates) const;

    ObjectOnFieldPtr getObject(int x, int y) const;

    int getXSize() const;

    int getYSize() const;

    /** Removes object */
    void removeObject(int x, int y, int z);

    /** Add object to board */
    void addObject(int x, int y, const ObjectOnFieldPtr &ptr);

    /** Check if move is possible and move if it is possible. */
    bool moveUp(int x, int y, int z);

    bool moveDown(int x, int y, int z);

    bool moveLeft(int x, int y, int z);

    bool moveRight(int x, int y, int z);

    /** Checks move impact, changes game status if should.
     * Especially checks if there is win or lose situation.
     * @param currentObject object which is moving.
     * @param nextObjects objects from the next object in the direction
     * of movement to the end of the board.
     * @return a pair of: 1. bool - indicates if move is possible
     * 2. int - how many objects will move in that direction (if they have isPush flag). */
    std::pair<bool, int> checkMoveImpact(const ObjectOnFieldPtr &currentObject,
                                         const ObjectOnFieldPtrs2Vector &nextObjects);

    /** Checks if move into objects in vector is possible (PUSH and STOP issues).
     * This method does not check if there is win or lose situation.
     * @param nextObjects objects from the next object in the direction
     * of movement to the end of the board.
     * @return a pair of: 1. bool - indicates if move is possible
     * 2. int - how many objects will move in that direction (if they have isPush flag). */
    std::pair<bool, int> isMovePossible(const ObjectOnFieldPtrs2Vector &nextObjects) const;

    /** Check if any object in vector has given flag set to true.
     * @param objectsOnField vector of ObjectOnFieldPtrs.
     * @param flag flag to check as string. */
    static bool anyObjectHasTrueFlag(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs,
                                     std::string flag);

    /** Finds solid objects which have isYou flag set to true from objects on board
     * and returns their coordinates. */
    std::vector<Coordinates> getYouObjectsCoordinates() const;

    void updateRules();
};