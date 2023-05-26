#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>

#include "ObjectOnField.h"
#include "SolidObject.h"

enum Action
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    WAIT
};

enum GameStatus
{
    IN_PROGRESS,
    WIN,
    LOSE
};

/* Struct to store coordinates of object on board*/
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

    /** Indicates if rules was changed in last move. */
    bool _wereRulesChanged = false;

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

    ObjectOnFieldPtr getemptyFieldPtr() const;

    int getXSize() const;

    int getYSize() const;

    int getZSize(int x, int y) const;

    GameStatus getGameStatus() const;

    /** Removes object */
    void removeObject(int x, int y, int z);
    void removeObject(const Coordinates &coordinates);

    /** Add object to board */
    void addObject(int x, int y, const ObjectOnFieldPtr &ptr);

    /** Check if move is possible and move if it is possible. */
    bool moveDown(int x, int y, int z);

    bool moveUp(int x, int y, int z);

    bool moveLeft(int x, int y, int z);

    bool moveRight(int x, int y, int z);

    void makeMove(ObjectOnFieldPtrs2Vector& nextObjects, ObjectOnFieldPtr &currentObject, int objectsToMove);

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
    static bool anyObjectHasProperty(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs,
                                     const std::string &property);

    /** Finds solid objects which have isYou flag set to true from objects on board
     * and returns their coordinates. */
    std::vector<Coordinates> getYouObjectsCoordinates() const;

    /** Updates rules. */
    void updateRules();

    /** Resets all properties of all SolidObjects on the board
     * and clear temporary identity of all objects. */
    void resetRules();

    /** If there are same objects on the same field, merge them. */
    void mergeSameObjects(std::vector<ObjectOnFieldPtr> &vector1);

    void anihilateSomeOfObjects(std::vector<ObjectOnFieldPtr> &vector1);

    bool checkWinConditions(std::vector<ObjectOnFieldPtr> &vector1) const;
};