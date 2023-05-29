#include <catch2/catch.hpp>

#include "../src/Board.h"
#include "../src/SolidObjects/Baba.h"
#include "../src/SolidObjects/Wall.h"
#include "../src/SolidObjects/Rock.h"
#include "../src/SolidObjects/Flag.h"
#include "../src/SolidObjects/Skull.h"
#include "../src/SolidObjects/Water.h"
#include "../src/SolidObjects/Lava.h"
#include "../src/Parameters.h"

TEST_CASE("Board tests general and move", "[Board]")
{
    Board board(3, 3);

    ObjectOnFieldPtr baba_ptr = std::make_shared<Baba>("baba.png");
    ObjectOnFieldPtr SolidObject_ptr = std::make_shared<SolidObject>("solidObject.png");
    ObjectOnFieldPtr wall_ptr = std::make_shared<Wall>();
    ObjectOnFieldPtr rock_ptr = std::make_shared<Rock>();
    ObjectOnFieldPtr flag_ptr = std::make_shared<Flag>();
    ObjectOnFieldPtr skull_ptr = std::make_shared<Skull>();
    ObjectOnFieldPtr water_ptr = std::make_shared<Water>();
    ObjectOnFieldPtr lava_ptr = std::make_shared<Lava>();
    flag_ptr->setProperty("Win", true);
    rock_ptr->setProperty("Stop", true);
    baba_ptr->setProperty("You", true);
    wall_ptr->setProperty("Push", true);
    skull_ptr->setProperty("Defeat", true);
    water_ptr->setProperty("Sink", true);
    lava_ptr->setProperty("Hot", true);

    board.addObject(0, 0, baba_ptr);
    board.addObject(0, 1, SolidObject_ptr);
    board.addObject(1, 0, SolidObject_ptr);
    board.addObject(1, 1, baba_ptr);
    board.addObject(1, 2, wall_ptr);
    board.addObject(2, 1, flag_ptr);

    SECTION("Getters")
    {
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 1, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(1, 0, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(1, 1, 0)->getImagePath() == "baba.png");

        CHECK(board.getXSize() == 3);
        CHECK(board.getYSize() == 3);
        CHECK(board.getZSize(0, 0) == 1);
    }

    SECTION("Add and remove objects")
    {
        board.removeObject(0, 0, 0);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == Parameters::OBJECT_PATHS.at("Empty"));

        board.addObject(0, 0, baba_ptr);
        board.addObject(0, 0, SolidObject_ptr);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 0, 1)->getImagePath() == "solidObject.png");

        board.removeObject(0, 0, 0);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "solidObject.png");
    }

    SECTION("Move")
    {
        board.moveDown(0, 0, 0);
        CHECK(board.getObject(0, 1, 1)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 0, 0)->getImagePath() == Parameters::OBJECT_PATHS.at("Empty"));

        board.moveRight(0, 1, 0);
        CHECK(board.getObject(0, 1, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(1, 1, 1)->getImagePath() == "solidObject.png");
    }

    SECTION("getYouObjects")
    {
        std::vector<Coordinates> coordinates = board.getObjectsToMoveCoordinates();
        CHECK(coordinates.size() == 2);
        Coordinates coordinates_1 = coordinates[0];
        Coordinates coordinates_2 = coordinates[1];
        CHECK(board.getObject(coordinates_1)->getImagePath() == "baba.png");
        CHECK(board.getObject(coordinates_2)->getImagePath() == "baba.png");
    }

    SECTION("True flag search")
    {
        std::vector<ObjectOnFieldPtr> ptrs1 = {wall_ptr, baba_ptr};
        std::vector<ObjectOnFieldPtr> ptrs2 = {SolidObject_ptr, SolidObject_ptr};
        CHECK(Board::anyObjectHasProperty(ptrs1, "You") == true);
        CHECK(Board::anyObjectHasProperty(ptrs1, "Push") == true);
        CHECK(Board::anyObjectHasProperty(ptrs2, "You") == false);
    }

    SECTION("Check if move is possible")
    {
        ObjectOnFieldPtrs2Vector ptrs1 = {{baba_ptr}, {SolidObject_ptr}, {wall_ptr}};
        ObjectOnFieldPtrs2Vector ptrs2 = {{wall_ptr}, {wall_ptr}, {SolidObject_ptr}};
        ObjectOnFieldPtrs2Vector ptrs3 = {{wall_ptr}, {wall_ptr}, {wall_ptr}};
        ObjectOnFieldPtrs2Vector ptrs4 = {{wall_ptr, baba_ptr}, {wall_ptr}, {wall_ptr},
                                          {SolidObject_ptr, SolidObject_ptr}};
        ObjectOnFieldPtrs2Vector ptrs5 = {{rock_ptr}};

        CHECK(board.isMovePossible(ptrs1).first == true);
        CHECK(board.isMovePossible(ptrs1).second == 0);
        CHECK(board.isMovePossible(ptrs2).first == true);
        CHECK(board.isMovePossible(ptrs2).second == 2);
        CHECK(board.isMovePossible(ptrs3).first == false);
        CHECK(board.isMovePossible(ptrs3).second == 0);
        CHECK(board.isMovePossible(ptrs4).first == true);
        CHECK(board.isMovePossible(ptrs4).second == 3);
        CHECK(board.isMovePossible(ptrs5).first == false);
        CHECK(board.isMovePossible(ptrs5).second == 0);
    }

    SECTION("Make move test")
    {
        ObjectOnFieldPtrs2Vector nextObjects = {{wall_ptr}, {wall_ptr}, {SolidObject_ptr}};
        ObjectOnFieldPtr currentObject = baba_ptr;
        int objectsToMove = 2;
        board.makeMove(nextObjects, currentObject, objectsToMove);
        CHECK(nextObjects[0][0]->getType() == "SolidObject");
        CHECK(nextObjects[0][0]->getImagePath() == "baba.png");
        CHECK(nextObjects[1][0]->getType() == "SolidObject");
        CHECK(nextObjects[1][0]->getImagePath() == "../" + Parameters::OBJECT_PATHS.at("Wall"));
        CHECK(nextObjects[2][1]->getImagePath() == "../" + Parameters::OBJECT_PATHS.at("Wall"));
    }

    SECTION("Move tests")
    {
        board.moveDown(1, 1, 0);
        CHECK(board.getObject(1, 2, 0)->getImagePath() == "../" + Parameters::OBJECT_PATHS.at("Wall"));
        CHECK(board.getZSize(1, 2) == 1);

        board.moveLeft(1, 1, 0);
        CHECK(board.getZSize(0, 1) == 2);
        CHECK(board.getObject(0, 1, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(0, 1, 1)->getImagePath() == "baba.png");

        board.moveRight(0, 1, 1);
        CHECK(board.getObject(1, 1, 0)->getImagePath() == "baba.png");

        board.moveUp(1, 1, 0);
        CHECK(board.getZSize(1, 0) == 2);
        CHECK(board.getObject(1, 0, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(1, 0, 1)->getImagePath() == "baba.png");
    }

    SECTION("Merge same objects test")
    {
        std::vector<ObjectOnFieldPtr> ptrs1 = {wall_ptr, wall_ptr, SolidObject_ptr};
        std::vector<ObjectOnFieldPtr> ptrs2 = {wall_ptr, SolidObject_ptr};
        std::vector<ObjectOnFieldPtr> ptrs3 = {wall_ptr, wall_ptr, wall_ptr};
        board.mergeSameObjects(ptrs1);
        CHECK(ptrs1.size() == 2);
        CHECK(ptrs1[0]->getImagePath() == "../" + Parameters::OBJECT_PATHS.at("Wall"));
        board.mergeSameObjects(ptrs2);
        CHECK(ptrs2.size() == 2);
        board.mergeSameObjects(ptrs3);
        CHECK(ptrs3.size() == 1);
    }

    SECTION("Check win condition test")
    {
        std::vector<ObjectOnFieldPtr> ptrs1 = {baba_ptr, wall_ptr, SolidObject_ptr};
        std::vector<ObjectOnFieldPtr> ptrs2 = {flag_ptr, baba_ptr};
        CHECK(board.checkWinConditions(ptrs1) == false);
        CHECK(board.checkWinConditions(ptrs2) == true);
        baba_ptr->setProperty("Win", true);
        CHECK(board.checkWinConditions(ptrs1) == true);
    }

    SECTION("Win test")
    {
        board.updateState(Action::RIGHT);
        board.updateState(Action::RIGHT);
        CHECK(board.getGameStatus() == GameStatus::WIN);
    }

    SECTION("Lose test")
    {
        board.removeObject(1, 1, 0);
        board.removeObject(0, 0, 0);
        board.updateState(Action::LEFT);
        CHECK(board.getGameStatus() == GameStatus::LOSE);
    }

    SECTION("Multiple move test")
    {
        board.updateState(Action::LEFT);
        board.updateState(Action::UP);
        CHECK(board.getObjectsToMoveCoordinates().size() == 1);
    }

    SECTION("Anihilate test")
    {
        std::vector<ObjectOnFieldPtr> ptrs1 = {wall_ptr, skull_ptr, baba_ptr};
        board.anihilateSomeOfObjects(ptrs1);
        CHECK(ptrs1.size() == 2);

        std::vector<ObjectOnFieldPtr> ptrs2 = {wall_ptr, water_ptr, baba_ptr};
        board.anihilateSomeOfObjects(ptrs2);
        CHECK(ptrs2.size() == 1);
        CHECK(ptrs2[0]->getType() == "Empty");

        baba_ptr->setProperty("Melt", true);
        std::vector<ObjectOnFieldPtr> ptrs3 = {lava_ptr, wall_ptr, baba_ptr};
        board.anihilateSomeOfObjects(ptrs3);
        CHECK(ptrs3.size() == 2);
    }
}