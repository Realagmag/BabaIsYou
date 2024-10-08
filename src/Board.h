#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>

#include "ObjectOnField.h"
#include "SolidObject.h"
#include "Parameters.h"
#include "Exceptions.h"

enum GameStatus
{
    IN_PROGRESS,
    WIN,
    LOSE
};

enum Action
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDO,
    WAIT
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
    unsigned int _xSize, _ySize;

    /** Status of the game */
    GameStatus _gameStatus;

    /** Indicates if rules was changed in last move. */
    bool _wereRulesChanged = false;

    /** Ptr to the empty field */
    ObjectOnFieldPtr _emptyFieldPtr;

    /** Archival game states */
    std::vector<ObjectOnFieldPtrs3Vector> _archivalStates;
    ObjectOnFieldPtrs3Vector _latestState;

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

    bool checkBoardCoordinatesValidity(int x, int y, int z) const;

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

    /** Returns index of first occurency of object with given type in the vector.
     * If there is no such object, returns -1. */
    static int objectWithTypeIndex(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs,
                                  const std::string &type);

    /** Finds solid objects which will move
     * and returns their coordinates. */
    std::vector<Coordinates> getObjectsToMoveCoordinates() const;

    static std::vector<int> indexesOfObjectsToPush(const std::vector<ObjectOnFieldPtr> &objectOnFieldPtrs);

    /** Updates rules. */
    void updateRules();

    /** Updates rules in the UpDown direction.
     * @param x x coordinate of the "IS" object.
     * @param y y coordinate of the "IS" object */
    void updateRulesUpDown(int x, int y);

    /** Updates rules in the LeftRight direction.
     * @param x x coordinate of the "IS" object.
     * @param y y coordinate of the "IS" object */
    void upadateRulesLeftRight(int x, int y);

    /** Resets all properties of all SolidObjects on the board
     * and clear temporary identity of all objects. */
    void resetRules();

    /** If there are same objects on the same field, merge them. */
    void mergeSameObjects(std::vector<ObjectOnFieldPtr> &vector1);

    /** Check if exist objects, which cannot be on the same field
    (for example: Sink object and objects which is not Float), if so, make specific action*/
    void anihilateSomeOfObjects(std::vector<ObjectOnFieldPtr> &vector1);

    bool checkWinConditions(const std::vector<ObjectOnFieldPtr> &vector1) const;

    void saveState(const ObjectOnFieldPtrs3Vector &state);

    /** Undo last move. */
    void undoMove();
};