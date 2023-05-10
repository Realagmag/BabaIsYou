#include <catch2/catch.hpp>

#include "../src/Board.h"
#include "../src/SolidObjects/Baba.h"

TEST_CASE("Board tests", "[Board]")
{
    Board board(2, 2);

    ObjectOnFieldPtr baba_ptr = std::make_shared<Baba>("baba.png");
    ObjectOnFieldPtr SolidObject_ptr = std::make_shared<SolidObject>("solidObject.png");
    baba_ptr->isYou = true;

    board.addObject(0, 0, baba_ptr);
    board.addObject(0, 1, SolidObject_ptr);
    board.addObject(1, 0, SolidObject_ptr);
    board.addObject(1, 1, baba_ptr);

    SECTION("Getters")
    {
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 1, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(1, 0, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(1, 1, 0)->getImagePath() == "baba.png");

        CHECK(board.getXSize() == 2);
        CHECK(board.getYSize() == 2);
    }

    SECTION("Add and remove objects")
    {
        board.removeObject(0, 0, 0);
        CHECK(board.getObject(0, 0, 0) == nullptr);

        board.addObject(0, 0, baba_ptr);
        board.addObject(0, 0, SolidObject_ptr);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 0, 1)->getImagePath() == "solidObject.png");

        board.removeObject(0, 0, 0);
        CHECK(board.getObject(0, 0, 0)->getImagePath() == "solidObject.png");
        CHECK(board.getObject(0, 0, 1) == nullptr);
    }

    SECTION("Move")
    {
        board.moveUp(0, 0, 0);
        CHECK(board.getObject(0, 1, 1)->getImagePath() == "baba.png");
        CHECK(board.getObject(0, 0, 0) == nullptr);

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
}
