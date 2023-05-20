#include <catch2/catch.hpp>

#include "../src/Board.h"
#include "../src/SolidObjects/Baba.h"
#include "../src/SolidObjects/Wall.h"
#include "../src/SolidObjects/Rock.h"
#include "../src/SolidObjects/Flag.h"
#include "../src/paths.h"

TEST_CASE("Board tests general and move", "[Board]")
{
    Board board(3, 3);

    ObjectOnFieldPtr baba_ptr = std::make_shared<Baba>("baba.png");
    ObjectOnFieldPtr SolidObject_ptr = std::make_shared<SolidObject>("solidObject.png");
    ObjectOnFieldPtr wall_ptr = std::make_shared<Wall>();
    ObjectOnFieldPtr rock_ptr = std::make_shared<Rock>();
    ObjectOnFieldPtr flag_ptr = std::make_shared<Flag>();
    flag_ptr->isWin = true;
    rock_ptr->isStop = true;
    baba_ptr->isYou = true;
    wall_ptr->isPush = true;

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
    }

    SECTION("Add and remove objects")
    {
        board.removeObject(0, 0, 0);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == paths.at("Empty"));

        board.addObject(0, 0, baba_ptr);
        board.addObject(0, 0, SolidObject_ptr);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 0, 1)->getImagePath() == "solidObject.png");

        board.removeObject(0, 0, 0);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "solidObject.png");
    }

    SECTION("Move")
    {
        board.moveUp(0, 0, 0);
        CHECK(board.getObject(0, 1, 1)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 0, 0)->getImagePath() == paths.at("Empty"));

        board.moveRight(0, 1, 0);
        CHECK(board.getObject(0, 1, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(1, 1, 1)->getImagePath() == "solidObject.png");
    }

    SECTION("getYouObjects")
    {
        std::vector<Coordinates> coordinates = board.getYouObjectsCoordinates();
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
        CHECK(Board::anyObjectHasTrueFlag(ptrs1, "isYou") == true);
        CHECK(Board::anyObjectHasTrueFlag(ptrs1, "isPush") == true);
        CHECK(Board::anyObjectHasTrueFlag(ptrs2, "isYou") == false);
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
        CHECK(board.isMovePossible(ptrs3).first == true);
        CHECK(board.isMovePossible(ptrs3).second == 0);
        CHECK(board.isMovePossible(ptrs4).first == true);
        CHECK(board.isMovePossible(ptrs4).second == 3);
        CHECK(board.isMovePossible(ptrs5).first == false);
        CHECK(board.isMovePossible(ptrs5).second == 0);
    }

    SECTION("Move tests")
    {
        board.moveUp(1, 1, 0);
        CHECK(board.getObject(1, 2, 0)->getImagePath() == "../" + paths.at("Wall"));
        CHECK(board.getObject(1, 2, 1)->getImagePath() == "baba.png");
    }
}
